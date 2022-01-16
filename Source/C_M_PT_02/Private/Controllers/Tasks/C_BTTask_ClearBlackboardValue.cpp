// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Tasks/C_BTTask_ClearBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UC_BTTask_ClearBlackboardValue::UC_BTTask_ClearBlackboardValue()
{
	NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UC_BTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	
	return EBTNodeResult::Succeeded;
}

void UC_BTTask_ClearBlackboardValue::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
