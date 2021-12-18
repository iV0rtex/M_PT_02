#include "Weapon.h"

#include "GameplayDebuggerTypes.h"
#include "Kismet/KismetSystemLibrary.h"

UWeapon::UWeapon()
{
	InitParams();
	
}

void UWeapon::Reload_Implementation()
{
	/*if(OnStartReload.IsBound())
	{
		OnStartReload.Broadcast();
	}*/
	bIsReloading = true;
	UseReloadAmmo();
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimeHandle,this,&UWeapon::EndReload,ReloadDuration);
}

bool UWeapon::Reload_Validate()
{
	return CanReload();
}

void UWeapon::PrintStartReloadAction() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Reload")));
}

void UWeapon::PrintEndReloadAction()const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Reloaded")));
	
}

void UWeapon::PrintFireAction()const
{
	const FString Message = FString::FromInt(CurrentAmmoInClip) +"/"+  FString::FromInt(CurrentAmmo);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Message);
}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitActions();
	
}

void UWeapon::InitParams()
{
	MuzzleSocketName = "Muzzle";
	Range = 1000;
	MaxAmmo = 20;
	AmmoPerClip = 5;
	ReloadDuration = 2.f;
	Damage = 500;
	
	CurrentAmmo = MaxAmmo;
	CurrentAmmoInClip = AmmoPerClip;
	bIsReloading = false;
}

void UWeapon::InitActions()
{
	/*OnFired.AddUFunction(this,"PrintFireAction");
	OnReloaded.AddUFunction(this,"PrintEndReloadAction");
	OnStartReload.AddUFunction(this,"PrintStartReloadAction");*/
}

bool UWeapon::CanFire() const
{
	if(!GetOwner()->HasAuthority())
	{
		return false;
	}
	return CurrentAmmoInClip > 0 && !bIsReloading;
}

void UWeapon::UseAmmo_Implementation()
{
	CurrentAmmoInClip--;
}

void UWeapon::Fire_Implementation()
{
	UseAmmo();
	WeaponTrace();

	/*if(OnFired.IsBound())
	{
		OnFired.Broadcast();
	}*/
}

bool UWeapon::Fire_Validate()
{
	return CanFire();
}

bool UWeapon::CanReload()
{
	if(!GetOwner()->HasAuthority())
	{
		return false;
	}
	if(CurrentAmmoInClip == AmmoPerClip || CurrentAmmo <= 0 || bIsReloading)
	{
		return false;
	}
	return true;
}

void UWeapon::EndReload_Implementation()
{
	bIsReloading = false;
	/*if(OnReloaded.IsBound())
	{
		OnReloaded.Broadcast();
	}*/
}


void UWeapon::UseReloadAmmo_Implementation()
{
	int32 AmmoForReload = AmmoPerClip - CurrentAmmoInClip;
	if(CurrentAmmo < AmmoForReload)
	{
		AmmoForReload = CurrentAmmo;
		CurrentAmmo = 0;
	}else
	{
		CurrentAmmo = CurrentAmmo - AmmoForReload;
	}

	CurrentAmmoInClip += AmmoForReload;
}

void UWeapon::WeaponTrace_Implementation() const
{
	const FName Name;
	const TArray<AActor*> Array;
	const FVector StartSocketLocation = GetSocketLocation(MuzzleSocketName);
	FHitResult OutHit;
	FVector EndSocketLocation = GetSocketLocation(MuzzleSocketName);
	FVector Forward = this->GetForwardVector();
	
	Forward = Forward * Range;
	EndSocketLocation = EndSocketLocation + Forward;
	
	UKismetSystemLibrary::LineTraceSingleByProfile(this,StartSocketLocation,EndSocketLocation,Name,false,Array,EDrawDebugTrace::ForDuration,OutHit,true,FLinearColor::Red,FLinearColor::Green,0.8f);
	
}

