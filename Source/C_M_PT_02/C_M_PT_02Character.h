// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerInventoryV2.h"
#include "Weapon.h"
#include "GameFramework/SaveGame.h"
#include "Interface/HittableInterface.h"
#include "Interface/WeaponryInterface.h"
#include "C_M_PT_02Character.generated.h"

class AInventoryItem;
DECLARE_EVENT_OneParam(AC_M_PT_02Character, FOnTookDamage, float);
DECLARE_EVENT(AC_M_PT_02Character,FOnDied);
DECLARE_EVENT(AC_M_PT_02Character,FOnHealed);
DECLARE_EVENT(AC_M_PT_02Character,FOnActivatedHeal);
DECLARE_EVENT(AC_M_PT_02Character,FOnDeactivatedHeal);
DECLARE_EVENT(AC_M_PT_02Character,FOnActivatedPeriodicDamage);
DECLARE_EVENT(AC_M_PT_02Character,FOnDeactivatePeriodicDamage);

UCLASS(config=Game)
class AC_M_PT_02Character : public ACharacter,public IWeaponryInterface, public IHittableInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPlayerInventoryV2* Inventory;
	
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UWeapon* WeaponComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UC_WeaponManagerComponent* WeaponManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UInventoryManagerComponent* InventoryManagerComponent;
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess= "true"))
	class UPawnNoiseEmitterComponent* NoiseEmitterComponent;

	UFUNCTION()
	void FastSaveGame();
	UFUNCTION()
	void FastDownloadGame();
	UFUNCTION()
	void GameSaved(const FString &Section, const int32 Index, bool bResult);
	UFUNCTION()
	void GameDownloaded(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	UFUNCTION(Server,Reliable)
	void ServerSetPlayerLocation(const FVector& NewLocation);

public:
	AC_M_PT_02Character();
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UPawnNoiseEmitterComponent* GetNoiseComp()const { return NoiseEmitterComponent; }

	float GetHealth() const;
	float GetMaxHealth() const;
	void GetItem(AInventoryItem* NewItem);

	UFUNCTION(BlueprintCallable)
	virtual void SetWeapon(AC_BaseWeapon* BaseWeapon) override;
	UFUNCTION(BlueprintCallable)
	void AddHealth(int32 Value);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	FOnTookDamage OnTookDamage;
	FOnDied OnDied;
	UPROPERTY(BlueprintReadWrite)
	bool bYouMustDieEffect;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHealth() const
	{
		return Health;
	}
	
	int32 MaxHealth;

	UC_WeaponManagerComponent* GetWeaponManager() const
	{
		return WeaponManagerComponent;
	}

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
	virtual void OnHit() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void Hit();
	UFUNCTION()
	void DropWeapon();
	UFUNCTION()
	void UseItem();
	UFUNCTION()
	void DropItem();

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated)
	int32 Health;
	
	FOnHealed OnHealed;
	FOnActivatedHeal OnActivatedHeal;
	FOnDeactivatedHeal OnDeactivatedHeal;
	FOnActivatedPeriodicDamage OnActivatedPeriodicDamage;
	FOnDeactivatePeriodicDamage OnDeactivatePeriodicDamage;
	FTimerHandle HealTimeHandle;
	FTimerHandle YouMustDieTimeHandle;
	
	float HealRate;
	float HealForTik;
	float Damage;
	float YouMustDieDamageEffectRate;
	
	
};

