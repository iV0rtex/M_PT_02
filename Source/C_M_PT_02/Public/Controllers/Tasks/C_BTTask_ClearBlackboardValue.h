// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BTTask_ClearBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UC_BTTask_ClearBlackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UC_BTTask_ClearBlackboardValue();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	
};
