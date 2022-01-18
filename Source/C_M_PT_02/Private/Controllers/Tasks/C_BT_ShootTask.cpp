// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Tasks/C_BT_ShootTask.h"

#include "AIController.h"
#include "C_ShooterPawn.h"
#include "C_M_PT_02/C_M_PT_02Character.h"

UC_BT_ShootTask::UC_BT_ShootTask()
{
}

EBTNodeResult::Type UC_BT_ShootTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AC_ShooterPawn* Character = Cast<AC_ShooterPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if(Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Character->Shoot();
	return EBTNodeResult::Succeeded;
}

void UC_BT_ShootTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
	
}
