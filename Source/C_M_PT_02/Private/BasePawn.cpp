// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "SpyCameraActor.h"
#include "Engine/CollisionProfile.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
	

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(50.f);
	SphereComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SetRootComponent(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(SphereComponent);

	SHealth.Health = 100;
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	WatchThroughActor = this;

	TArray<AActor*> CameraList;
	UGameplayStatics::GetAllActorsOfClass(this,ASpyCameraActor::StaticClass(),CameraList);
	for(AActor * CameraActor : CameraList)
	{
		ASpyCameraActor * Camera = Cast<ASpyCameraActor>(CameraActor);
		if(Camera)
		{
			Camera->OnPlayerDetected.AddUFunction(this,"SetPlayerDetectedStatus");
			Camera->OnPlayerGone.AddUFunction(this,"UnsetPlayerDetectedStatus");	
		}
		
	}

	OnTookDamage.AddUFunction(this,"PrintHealth");
	
}

void ABasePawn::MoveForward(float Val)
{
	if(Val != 0.f && WatchThroughActor != nullptr)
	{
		AddMovementInput(WatchThroughActor->GetActorForwardVector(),Val);
	}
}

void ABasePawn::MoveRight(float Val)
{
	if(Val != 0.f && WatchThroughActor != nullptr)
	{
		AddMovementInput(WatchThroughActor->GetActorRightVector(),Val);
	}
}

void ABasePawn::SetPlayerDetectedStatus()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Player detected")));
	OnDetectedColor.Broadcast();
}

void ABasePawn::UnsetPlayerDetectedStatus()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Player undetected")));
	OnDefaultColor.Broadcast();
}

void ABasePawn::PrintHealth() const
{
	const FString Message = FString::Printf(TEXT("Health:%f"),SHealth.Health);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Message);
}


// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABasePawn::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABasePawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

}

void ABasePawn::Damage(const float Damage)
{
	SHealth.Health -= Damage;
	if(SHealth.Health < 0)
	{
		SHealth.Health = 0;
	}
	OnTookDamage.Broadcast();
}

