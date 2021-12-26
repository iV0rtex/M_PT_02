// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_M_PT_02/WeaponReloadInterface.h"
#include "C_M_PT_02/Weapon/C_BaseWeapon.h"
#include "C_FireWeapon.generated.h"

DECLARE_EVENT(AC_FireWeapon, FOnReloaded);
DECLARE_EVENT(AC_FireWeapon, FOnStartReload);
DECLARE_EVENT(AC_FireWeapon, FOnFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractWeaponMulticast);

UCLASS()
class C_M_PT_02_API AC_FireWeapon : public AC_BaseWeapon,public IWeaponReloadInterface
{
	GENERATED_BODY()
	
	FTimerHandle ReloadTimeHandle;

	FOnReloaded OnReloaded;
	FOnStartReload OnStartReload;
	

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Range;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 AmmoPerClip;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 MaxAmmo;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float ReloadDuration;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float FireDuration;
	UPROPERTY(BlueprintAssignable)
	FInteractWeaponMulticast OnInteractWeaponMulticast;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystem* ParticleSystem;

	UFUNCTION(Server,Unreliable)
	void UseReloadAmmo();
	UFUNCTION(Server,Unreliable)
	void EndReload();
	UFUNCTION(Server,Unreliable)
	void UseAmmo();
	UFUNCTION(Server,Unreliable)
	void Fire();
	UFUNCTION(Server,Unreliable)
	void LaunchBullet();
	UFUNCTION(Server,Unreliable)
	void EndFire();
	
	UFUNCTION(NetMulticast,Unreliable)
	void FireEffectMulticast();
	
	UPROPERTY()
	int32 CurrentAmmo;
	UPROPERTY()
	int32 CurrentAmmoInClip;
	UPROPERTY()
	bool bIsReloading;
	bool bCanFire;
	FTimerHandle FireTimeHandle;
	FOnFired OnFired;
	
	virtual bool CanReload() override;
	virtual bool CanFire() const;
	virtual void OnDrop() override;

	

public:
	AC_FireWeapon();
	
	UFUNCTION(Server,Unreliable)
	virtual void InteractWeapon() override;
	UFUNCTION(Server,Unreliable)
	virtual void Reload() override;

	UFUNCTION()
	void PrintStartReloadAction() const;
	UFUNCTION()
	void PrintEndReloadAction() const;
	UFUNCTION()
	void PrintFireAction() const;
};