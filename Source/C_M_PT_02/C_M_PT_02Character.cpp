#include "C_M_PT_02Character.h"

#include "GameplayDebuggerTypes.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "PlayerInventoryV2.h"
#include "ShooterMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Core/C_FirstSaveGame.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Inventory/InventoryManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/C_WeaponManagerComponent.h"
#include "Blueprint/UserWidget.h"

void AC_M_PT_02Character::FastSaveGame()
{
	if (UC_FirstSaveGame* SaveGameInstance = Cast<UC_FirstSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_FirstSaveGame::StaticClass())))
	{
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		SavedDelegate.BindUObject(this, &AC_M_PT_02Character::GameSaved);
		
		SaveGameInstance->PlayerHealth = GetHealth();
		SaveGameInstance->PlayerPosition = GetActorLocation();
		
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, TEXT("PlayerData"), 0, SavedDelegate);
	}

}

void AC_M_PT_02Character::FastDownloadGame()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &AC_M_PT_02Character::GameDownloaded);
	UGameplayStatics::AsyncLoadGameFromSlot(TEXT("PlayerData"), 0, LoadedDelegate);
}

void AC_M_PT_02Character::GameSaved(const FString& Section, const int32 Index, bool bResult)
{
	if(bResult)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Game has been saved")));
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Save error occured")));
	}
}

void AC_M_PT_02Character::GameDownloaded(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UC_FirstSaveGame * Data = Cast<UC_FirstSaveGame>(LoadedGameData);
	if(Data)
	{
		Health = Data->PlayerHealth;
		ServerSetPlayerLocation(Data->PlayerPosition);
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Game has been loaded")));
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Downloading error occured")));
	}
}

void AC_M_PT_02Character::ServerSetPlayerLocation_Implementation(const FVector& NewLocation)
{
	SetActorLocation(NewLocation);
}

AC_M_PT_02Character::AC_M_PT_02Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	Inventory = CreateDefaultSubobject<UPlayerInventoryV2>(TEXT("Inventory"));
	
	/*USkeletalMeshComponent* MeshL = GetMesh();
	WeaponComponent = CreateDefaultSubobject<UWeapon>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(MeshL);*/ //Old weapon realization

	WeaponManagerComponent = CreateDefaultSubobject<UC_WeaponManagerComponent>(TEXT("WeaponManager"));
	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("InventoryManager"));
	NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
	
	MaxHealth = 100;
	Health = MaxHealth;
	HealRate = 2.f;
	HealForTik = 3.f;
	Damage = 10.f;
	YouMustDieDamageEffectRate = 1.f;
	bYouMustDieEffect = false;
}

void AC_M_PT_02Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AC_M_PT_02Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_M_PT_02Character::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AC_M_PT_02Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AC_M_PT_02Character::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AC_M_PT_02Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AC_M_PT_02Character::TouchStopped);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AC_M_PT_02Character::OnResetVR);
	
	/*PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeapon::Fire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeapon::Reload);*/ //Old weapon realization

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponManagerComponent, &UC_WeaponManagerComponent::ReloadCurrentWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponManagerComponent, &UC_WeaponManagerComponent::InteractCurrentWeapon);
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &AC_M_PT_02Character::DropWeapon);
	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &AC_M_PT_02Character::UseItem);
	PlayerInputComponent->BindAction("DropItem", IE_Pressed, this, &AC_M_PT_02Character::DropItem);
	PlayerInputComponent->BindAction("FastSaveGame", IE_Pressed, this, &AC_M_PT_02Character::FastSaveGame);
	PlayerInputComponent->BindAction("FastDownloadGame", IE_Pressed, this, &AC_M_PT_02Character::FastDownloadGame);
}

void AC_M_PT_02Character::BeginPlay()
{
	Super::BeginPlay();

	/*UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->OnComponentBeginOverlap.AddDynamic(this,&AC_M_PT_02Character::OnComponentBeginOverlap);*/
	
	OnTookDamage.AddUFunction(this,"ActivatePeriodicHeal");
	OnTookDamage.AddUFunction(this,"PrintDamage");

	OnDied.AddUFunction(this,"PrintDiedStatus");
	OnDied.AddUFunction(this,"DeactivatePeriodicHeal");
	OnDied.AddUFunction(this,"DeactivatePeriodicDamage");
	
	OnHealed.AddUFunction(this,"DeactivatePeriodicHeal");
	OnHealed.AddUFunction(this,"PrintHeal");
	
	OnActivatedHeal.AddUFunction(this,"PrintActivateHeal");
	OnDeactivatedHeal.AddUFunction(this,"PrintDeactivateHeal");
	OnActivatedPeriodicDamage.AddUFunction(this,"PrintActivatePeriodicalDamage");
	OnDeactivatePeriodicDamage.AddUFunction(this,"PrintDeactivatePeriodicalDamage");

	auto* Settings = GEngine->GetGameUserSettings();

}

void AC_M_PT_02Character::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}

void AC_M_PT_02Character::OnHit()
{
	if(bYouMustDieEffect )
	{
		ActivatePeriodicDamage();
		
	}else
	{
		Hit();
	}
}

void AC_M_PT_02Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_M_PT_02Character, Health)
}


void AC_M_PT_02Character::Hit()
{
	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this]
	{
		int32 NewHealth = Health - Damage;
		if(NewHealth < 0)
		{
			NewHealth = 0;
		}
		AsyncTask(ENamedThreads::GameThread, [this,NewHealth]
		{
			Health = NewHealth;
			if(Health == 0 && OnDied.IsBound())
			{
				OnDied.Broadcast();
			}else if(OnTookDamage.IsBound())
			{
				OnTookDamage.Broadcast(Damage);
			}
		});
	});
}

void AC_M_PT_02Character::DropWeapon()
{
	if(WeaponManagerComponent)
	{
		WeaponManagerComponent->DropCurrentWeapon();
	}
}

void AC_M_PT_02Character::UseItem()
{
	if(InventoryManagerComponent)
	{
		InventoryManagerComponent->ServerUseFirstItem();
	}
}

void AC_M_PT_02Character::DropItem()
{
	if(InventoryManagerComponent)
	{
		InventoryManagerComponent->ServerDropFirstItem();
	}
	
}

void AC_M_PT_02Character::OnHeal()
{
	Health += HealForTik;
	if(Health > MaxHealth)
	{
		Health = MaxHealth;
	}
	if(OnHealed.IsBound())
	{
		OnHealed.Broadcast();
	}
}


void AC_M_PT_02Character::ActivatePeriodicHeal()
{
	if(!GetWorldTimerManager().IsTimerActive(HealTimeHandle) && Health < MaxHealth && Health > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimeHandle,this,&AC_M_PT_02Character::OnHeal,HealRate,true);

		if(OnActivatedHeal.IsBound())
		{
			OnActivatedHeal.Broadcast();
		}
	}
}

void AC_M_PT_02Character::DeactivatePeriodicHeal()
{
	if(Health == MaxHealth || Health == 0)
	{
		GetWorldTimerManager().ClearTimer(HealTimeHandle);
		if(OnDeactivatedHeal.IsBound())
		{
			OnDeactivatedHeal.Broadcast();
		}
	}
}

void AC_M_PT_02Character::ActivatePeriodicDamage()
{
	if(!GetWorldTimerManager().IsTimerActive(YouMustDieTimeHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(YouMustDieTimeHandle,this,&AC_M_PT_02Character::Hit,YouMustDieDamageEffectRate,true);
		if(OnActivatedPeriodicDamage.IsBound())
		{
			OnActivatedPeriodicDamage.Broadcast();
		}
	}
	
}

void AC_M_PT_02Character::DeactivatePeriodicDamage()
{
	if(Health == 0 || (!bYouMustDieEffect && GetWorldTimerManager().IsTimerActive(YouMustDieTimeHandle)))
	{
		GetWorldTimerManager().ClearTimer(YouMustDieTimeHandle);
		if(OnDeactivatePeriodicDamage.IsBound())
		{
			OnDeactivatePeriodicDamage.Broadcast();
		}
	}
}

void AC_M_PT_02Character::PrintDamage(const float LDamage) const
{
	const FString Message = "You took  " + FString::SanitizeFloat(LDamage) + " Damage";
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
}

void AC_M_PT_02Character::PrintHeal() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Took Heal")));
}

void AC_M_PT_02Character::PrintActivateHeal() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Heal Activated")));
}

void AC_M_PT_02Character::PrintDeactivateHeal() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Heal Deactivated")));
}

void AC_M_PT_02Character::PrintActivatePeriodicalDamage() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Pereodical damage Activate")));
}

void AC_M_PT_02Character::PrintDeactivatePeriodicalDamage() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Pereodical damage DEactivate")));
}

void AC_M_PT_02Character::PrintDiedStatus() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("YOU DIED")));
}

float AC_M_PT_02Character::GetHealth() const
{
	return Health;
}

float AC_M_PT_02Character::GetMaxHealth() const
{
	return MaxHealth;
}

void AC_M_PT_02Character::GetItem(AInventoryItem* NewItem)
{
	if(InventoryManagerComponent)
	{
		InventoryManagerComponent->ServerAddItem(NewItem,1);
	}
}

void AC_M_PT_02Character::SetWeapon(AC_BaseWeapon* BaseWeapon)
{
	WeaponManagerComponent->SetCurrentWeapon(BaseWeapon);
}

void AC_M_PT_02Character::AddHealth(int32 Value)
{
	if(GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	Health += Value;
	if(Health > MaxHealth)
	{
		Health = MaxHealth;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current Health: %i"),Health));
}


void AC_M_PT_02Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AC_M_PT_02Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AC_M_PT_02Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AC_M_PT_02Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AC_M_PT_02Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AC_M_PT_02Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AC_M_PT_02Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
