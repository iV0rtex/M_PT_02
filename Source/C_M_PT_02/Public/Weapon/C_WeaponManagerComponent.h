// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_M_PT_02/Weapon/C_BaseWeapon.h"
#include "C_WeaponManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_M_PT_02_API UC_WeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_WeaponManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int32 DistanceToDropWeapon;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AC_BaseWeapon * CurrentWeapon;

	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void SetCurrentWeapon(AC_BaseWeapon* NewWeapon);
	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void DropCurrentWeapon();

	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void InteractCurrentWeapon();
	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void ReloadCurrentWeapon();

		
};
