// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerInventoryV2.h"
#include "Weapon.h"
#include "Interface/WeaponryInterface.h"
#include "C_M_PT_02Character.generated.h"

DECLARE_EVENT_OneParam(AC_M_PT_02Character,FOnTookDamage,float);
DECLARE_EVENT(AC_M_PT_02Character,FOnDied);
DECLARE_EVENT(AC_M_PT_02Character,FOnHealed);
DECLARE_EVENT(AC_M_PT_02Character,FOnActivatedHeal);
DECLARE_EVENT(AC_M_PT_02Character,FOnDeactivatedHeal);
DECLARE_EVENT(AC_M_PT_02Character,FOnActivatedPeriodicDamage);
DECLARE_EVENT(AC_M_PT_02Character,FOnDeactivatePeriodicDamage);

UCLASS(config=Game)
class AC_M_PT_02Character : public ACharacter,public IWeaponryInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UC_WeaponManagerComponent* WeaponManagerComponent;
public:
	AC_M_PT_02Character();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	void OnResetVR();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable)
	void OnHit();
	
	UFUNCTION()
	void Hit();

	UFUNCTION()
	void OnHeal();
	UFUNCTION()
	void ActivatePeriodicHeal();
	UFUNCTION()
	void DeactivatePeriodicHeal();
	UFUNCTION()
	void ActivatePeriodicDamage();
	UFUNCTION()
	void DeactivatePeriodicDamage();
	UFUNCTION()
	void PrintDamage(const float LDamage) const;
	UFUNCTION()
	void PrintHeal() const;
	UFUNCTION()
	void PrintActivateHeal() const;
	UFUNCTION()
	void PrintDeactivateHeal() const;
	UFUNCTION()
	void PrintActivatePeriodicalDamage() const;
	UFUNCTION()
	void PrintDeactivatePeriodicalDamage() const;
	UFUNCTION()
	void PrintDiedStatus() const;

	
	FOnHealed OnHealed;
	FOnActivatedHeal OnActivatedHeal;
	FOnDeactivatedHeal OnDeactivatedHeal;
	FOnActivatedPeriodicDamage OnActivatedPeriodicDamage;
	FOnDeactivatePeriodicDamage OnDeactivatePeriodicDamage;
	FTimerHandle HealTimeHandle;
	FTimerHandle YouMustDieTimeHandle;

	float MaxHealth;
	float Health;
	float HealRate;
	float HealForTik;
	float Damage;
	float YouMustDieDamageEffectRate;
	

public:
	FOnTookDamage OnTookDamage;
	FOnDied OnDied;
	
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPlayerInventoryV2* Inventory;
	
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly)
	UWeapon* WeaponComponent;
	
	UPROPERTY(BlueprintReadWrite)
	bool bYouMustDieEffect;
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	float GetHealth() const;
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetWeapon(AC_BaseWeapon* BaseWeapon) override;
};

