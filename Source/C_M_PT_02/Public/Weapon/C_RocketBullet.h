// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/C_BaseBullet.h"
#include "C_RocketBullet.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API AC_RocketBullet : public AC_BaseBullet
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UParticleSystem* ParticleSystem;
	
	UFUNCTION() 
	void DestroyBulletMulticast();
};
