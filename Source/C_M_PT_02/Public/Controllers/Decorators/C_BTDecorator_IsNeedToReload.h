// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "C_BTDecorator_IsNeedToReload.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UC_BTDecorator_IsNeedToReload : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UC_BTDecorator_IsNeedToReload();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	
};
