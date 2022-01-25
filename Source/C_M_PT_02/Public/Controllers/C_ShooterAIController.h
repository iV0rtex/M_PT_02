// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API AC_ShooterAIController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	virtual FGenericTeamId GetGenericTeamId() const override;
public:
	AC_ShooterAIController();
	virtual void BeginPlay() override;
};
