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

protected:
	UPROPERTY()
	FName MuzzleSocketName;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Range;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 MaxAmmo;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 AmmoPerClip;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float ReloadDuration;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float Damage;

	UPROPERTY()
	int32 CurrentAmmo;
	UPROPERTY()
	int32 CurrentAmmoInClip;
	UPROPERTY()
	bool bIsReloading;
	
	bool CanFire() const;
	
	UFUNCTION(Server,Reliable)
	void UseAmmo();

	
	virtual bool CanReload() override;
	UFUNCTION(Server,Unreliable)
	void EndReload();
	UFUNCTION(Server,Unreliable)
	void UseReloadAmmo();

	UFUNCTION(NetMulticast,Reliable)
	void WeaponTrace() const;

	FOnReloaded OnReloaded;
	FOnStartReload OnStartReload;
	FOnFired OnFired;

public:
	
	UFUNCTION(Server,Reliable)
	void Fire();
	UFUNCTION(Server,Reliable)
	virtual void Reload() override;
	
	UFUNCTION()
	void PrintStartReloadAction() const;
	UFUNCTION()
	void PrintEndReloadAction() const;
	UFUNCTION()
	void PrintFireAction() const;
	
	virtual void BeginPlay() override;
};
