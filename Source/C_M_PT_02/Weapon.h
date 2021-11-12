#pragma once

#include "CoreMinimal.h"
#include "WeaponReloadInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Weapon.generated.h"

DECLARE_EVENT(UWeapon, FOnReloaded);
DECLARE_EVENT(UWeapon, FOnStartReload);
DECLARE_EVENT(UWeapon, FOnFired);

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C_M_PT_02_API UWeapon : public UStaticMeshComponent, public IWeaponReloadInterface
{
	GENERATED_BODY()

	UWeapon();
	FTimerHandle ReloadTimeHandle;

	void InitParams();
	void InitActions();

public:
	UPROPERTY()
	FName MuzzleSocketName;
	UPROPERTY(VisibleAnywhere)
	int32 Range;
	UPROPERTY(VisibleAnywhere)
	int32 MaxAmmo;
	UPROPERTY(VisibleAnywhere)
	int32 AmmoPerClip;
	UPROPERTY(VisibleAnywhere)
	float ReloadDuration;
	UPROPERTY(VisibleAnywhere)
	float Damage;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentAmmo;
	UPROPERTY(VisibleAnywhere)
	int32 CurrentAmmoInClip;
	UPROPERTY(VisibleAnywhere)
	bool bIsReloading;

	
	UFUNCTION(BlueprintCallable)
	void Fire();
	bool CanFire() const;
	void UseAmmo();

	UFUNCTION(BlueprintCallable)
	virtual void Reload() override;
	virtual bool CanReload() override;
	void EndReload();
	void UseReloadAmmo();
	
	void WeaponTrace() const;

	FOnReloaded OnReloaded;
	FOnStartReload OnStartReload;
	FOnFired OnFired;

	UFUNCTION(BlueprintCallable)
	void PrintStartReloadAction() const;
	UFUNCTION(BlueprintCallable)
	void PrintEndReloadAction() const;
	UFUNCTION(BlueprintCallable)
	void PrintFireAction() const;
	virtual void BeginPlay() override;
};
