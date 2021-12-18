// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/C_FireWeapon.h"
#include "C_PistolWeapon.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API AC_PistolWeapon : public AC_FireWeapon
{
	GENERATED_BODY()

	FTimerHandle FireTimeHandle;
	
	AC_PistolWeapon();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float FireDuration;
	
	bool bCanFire;

	UFUNCTION(Server,Unreliable)
	void EndFire();

	virtual bool CanFire() const override;

public:
	virtual void InteractWeapon() override;
	
};
