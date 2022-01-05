// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_FireWeapon.h"

#include "DrawDebugHelpers.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "Kismet/GameplayStatics.h"

AC_FireWeapon::AC_FireWeapon()
{
	Range = 10000;
	MaxAmmo = 20;
	AmmoPerClip = 5;
	ReloadDuration = 2.f;
	CurrentAmmo = MaxAmmo;
	CurrentAmmoInClip = AmmoPerClip;
	bIsReloading = false;
	bCanFire = true;
	FireDuration = .6f;
}

void AC_FireWeapon::BeginPlay()
{
	Super::BeginPlay();

	OnFired.AddUFunction(this,"PrintFireAction");
	OnReloaded.AddUFunction(this,"PrintEndReloadAction");
	OnStartReload.AddUFunction(this,"PrintStartReloadAction");
}

void AC_FireWeapon::PrintStartReloadAction() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Reload")));
}

void AC_FireWeapon::PrintEndReloadAction() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Reloaded")));
}

void AC_FireWeapon::PrintFireAction() const
{
	const FString Message = FString::FromInt(CurrentAmmoInClip) +"/"+  FString::FromInt(CurrentAmmo);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Message);
}

void AC_FireWeapon::ServerUseReloadAmmo_Implementation()
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

void AC_FireWeapon::ServerEndReload_Implementation()
{
	ServerUseReloadAmmo();
	bIsReloading = false;
	if(OnReloaded.IsBound())
	{
		OnReloaded.Broadcast();
	}
}

void AC_FireWeapon::ServerUseAmmo_Implementation()
{
	CurrentAmmoInClip--;
}

void AC_FireWeapon::ServerFire_Implementation()
{
	FireEffectMulticast();
	if(OnInteractWeaponMulticast.IsBound())
	{
		OnInteractWeaponMulticast.Broadcast();
	}
	ServerLaunchBullet();

	if(OnFired.IsBound())
	{
		OnFired.Broadcast();
	}
}

void AC_FireWeapon::FireEffectMulticast_Implementation()
{
	if(GetNetMode() == NM_DedicatedServer)
	{
		return;
	}
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ParticleSystem,
		GetStaticMeshComponent()->GetSocketTransform("Muzzle",RTS_World),
		true,
		EPSCPoolMethod::AutoRelease,
		true
	);
}

void AC_FireWeapon::ServerLaunchBullet_Implementation()
{
	const FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	const FRotator Rotation = this->GetActorRotation();
	GetWorld()->SpawnActor(Bullet,&LocationSocket,&Rotation);
}

bool AC_FireWeapon::CanReload()
{
	/*if(!GetOwner()->HasAuthority())
	{
		return false;
	}*///TODO: Fix it
	if(CurrentAmmoInClip == AmmoPerClip || CurrentAmmo <= 0 || bIsReloading)
	{
		return false;
	}
	return true;
}

bool AC_FireWeapon::CanFire() const
{
	/*if(!GetOwner()->HasAuthority())
	{
		return false;
	}*/ //TODO: Fix it
	return bCanFire && CurrentAmmoInClip > 0 && !bIsReloading;
}

void AC_FireWeapon::OnDrop()
{
	bIsReloading = false;
	if(GetWorld()->GetTimerManager().IsTimerActive(ReloadTimeHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimeHandle);
	}
}

void AC_FireWeapon::ServerReload_Implementation()
{
	if(!CanReload())
	{
		return;
	}
	if(OnStartReload.IsBound())
	{
		OnStartReload.Broadcast();
	}
	bIsReloading = true;
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimeHandle,this,&AC_FireWeapon::ServerEndReload,ReloadDuration);
}

void AC_FireWeapon::ServerInteractWeapon_Implementation()
{
	if (!CanFire())
	{
		return;
	}
	ServerUseAmmo();
	ServerFire();
	bCanFire = false;
	GetWorld()->GetTimerManager().SetTimer(FireTimeHandle,this,&AC_FireWeapon::ServerEndFire,FireDuration);
}
void AC_FireWeapon::ServerEndFire_Implementation()
{
	bCanFire = true;
}


