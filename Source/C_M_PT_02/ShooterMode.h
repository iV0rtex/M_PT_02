// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterMode.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API AShooterMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	float Scores;
	
	UFUNCTION()
	void OnTurretKilled();
	
};
