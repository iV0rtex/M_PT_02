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

void AC_FireWeapon::UseReloadAmmo_Implementation()
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

void AC_FireWeapon::EndReload_Implementation()
{
	UseReloadAmmo();
	bIsReloading = false;
	if(OnReloaded.IsBound())
	{
		OnReloaded.Broadcast();
	}
}

void AC_FireWeapon::UseAmmo_Implementation()
{
	CurrentAmmoInClip--;
}

void AC_FireWeapon::Fire_Implementation()
{
	FireEffectMulticast();
	if(OnInteractWeaponMulticast.IsBound())
	{
		OnInteractWeaponMulticast.Broadcast();
	}
	LaunchBullet();

	if(OnFired.IsBound())
	{
		OnFired.Broadcast();
	}
}

void AC_FireWeapon::FireEffectMulticast_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ParticleSystem,
		GetStaticMeshComponent()->GetSocketTransform("Muzzle",RTS_World),
		true,
		EPSCPoolMethod::AutoRelease,
		true
	);
}

void AC_FireWeapon::LaunchBullet_Implementation()
{
	FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	FCollisionQueryParams RV_TraceParams;
	RV_TraceParams.bTraceComplex = true;
	FHitResult RV_Hit(ForceInit);
	FVector LocationEnd = LocationSocket;
	FVector Forward = this->GetActorForwardVector();
	Forward = Forward * Range;
	LocationEnd += Forward;
	GetWorld()->LineTraceSingleByChannel(
	   RV_Hit,
	   LocationSocket,
	   LocationEnd,
	   ECC_Pawn,
	   RV_TraceParams
	);
	DrawDebugLine(
	   GetWorld(),
	   LocationSocket,
	   LocationEnd,
	   FColor(255, 0, 0),
	   false,
	   0.3,
	   0,
	   2
	   );
	if (RV_Hit.bBlockingHit)
	{
		auto* Character = Cast<AC_M_PT_02Character>(RV_Hit.GetActor());
		if (Character)
		{
			//Character->ApplyDamage(Damage); //TODO: for the future updates
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
	}
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

void AC_FireWeapon::Reload_Implementation()
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
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimeHandle,this,&AC_FireWeapon::EndReload,ReloadDuration);
}

void AC_FireWeapon::InteractWeapon_Implementation()
{
	if (!CanFire())
	{
		return;
	}
	UseAmmo();
	Fire();
	bCanFire = false;
	GetWorld()->GetTimerManager().SetTimer(FireTimeHandle,this,&AC_FireWeapon::EndFire,FireDuration);
}
void AC_FireWeapon::EndFire_Implementation()
{
	bCanFire = true;
}


