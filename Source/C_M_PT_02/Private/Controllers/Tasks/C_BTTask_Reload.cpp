// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Tasks/C_BTTask_Reload.h"

#include "AIController.h"
#include "C_ShooterPawn.h"
#include "Weapon/C_WeaponManagerComponent.h"

UC_BTTask_Reload::UC_BTTask_Reload()
{
	NodeName = "Reload weapon";
}

EBTNodeResult::Type UC_BTTask_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AC_ShooterPawn* Character = Cast<AC_ShooterPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if(Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	Character->GetWeaponManager()->ReloadCurrentWeapon();
	
	return EBTNodeResult::Succeeded;
}

void UC_BTTask_Reload::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
