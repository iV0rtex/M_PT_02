// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/C_FireWeapon.h"
#include "C_ShotgunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API AC_ShotgunWeapon : public AC_FireWeapon
{
	GENERATED_BODY()
	AC_ShotgunWeapon();
	UPROPERTY(EditAnywhere)
	int32 BulletAmount;

protected:
	virtual void LaunchBullet_Implementation() override;
	
};
