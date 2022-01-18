// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "C_BTService_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UC_BTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UC_BTService_PlayerLocation();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	
};
