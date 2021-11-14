// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerInventoryV2.h"
#include "Weapon.h"
#include "C_M_PT_02Character.generated.h"

DECLARE_EVENT_OneParam(AC_M_PT_02Character,FOnTookDamage,float);
DECLARE_EVENT(AC_M_PT_02Character,FOnDied);
DECLARE_EVENT(AC_M_PT_02Character,FOnHealed);
DECLARE_EVENT(AC_M_PT_02Character,FOnActivatedHeal);
DECLARE_EVENT(AC_M_PT_02Character,FOnDeactivatedHeal);
DECLARE_EVENT(AC_M_PT_02Character,FOnActivatedPeriodicDamage);
DECLARE_EVENT(AC_M_PT_02Character,FOnDeactivatePeriodicDamage);

UCLASS(config=Game)
class AC_M_PT_02Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AC_M_PT_02Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

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
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	float GetHealth() const;
	float GetMaxHealth() const;
};

