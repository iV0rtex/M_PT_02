#pragma once

//OLD WEAPON REALIZATION 

#include "CoreMinimal.h"
#include "WeaponReloadInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Weapon.generated.h"

/*DECLARE_EVENT(UWeapon, FOnReloaded);
DECLARE_EVENT(UWeapon, FOnStartReload);
DECLARE_EVENT(UWeapon, FOnFired);*/

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
	void ServerUseAmmo();

	
	virtual bool CanReload() override;
	UFUNCTION(Server,Unreliable)
	void ServerEndReload();
	UFUNCTION(Server,Unreliable)
	void ServerUseReloadAmmo();

	UFUNCTION(NetMulticast,Reliable)
	void WeaponTrace() const;

	/*FOnReloaded OnReloaded;
	FOnStartReload OnStartReload;
	FOnFired OnFired;*/

public:
	
	UFUNCTION(Server,Reliable, WithValidation)
	void ServerFire();
	UFUNCTION(Server,Reliable, WithValidation)
	virtual void ServerReload() override;
	
	UFUNCTION()
	void PrintStartReloadAction() const;
	UFUNCTION()
	void PrintEndReloadAction() const;
	UFUNCTION()
	void PrintFireAction() const;
	
	virtual void BeginPlay() override;
};
