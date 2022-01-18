// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BT_ShootTask.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UC_BT_ShootTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UC_BT_ShootTask();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
};
