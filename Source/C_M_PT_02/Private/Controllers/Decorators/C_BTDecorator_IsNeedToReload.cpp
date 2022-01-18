// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Decorators/C_BTDecorator_IsNeedToReload.h"

#include "AIController.h"
#include "C_ShooterPawn.h"
#include "Weapon/C_WeaponManagerComponent.h"

UC_BTDecorator_IsNeedToReload::UC_BTDecorator_IsNeedToReload()
{
	NodeName = "Is need to reload";
}

bool UC_BTDecorator_IsNeedToReload::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                               uint8* NodeMemory) const
{
	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	//TODO: 
	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Check")));
	AC_ShooterPawn* Character = Cast<AC_ShooterPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if(Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}*/
	
	//Character->GetWeaponManager()
}

void UC_BTDecorator_IsNeedToReload::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UC_BTDecorator_IsNeedToReload::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}
