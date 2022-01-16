// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Services/C_BTService_SetPlayerIfSeen.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UC_BTService_SetPlayerIfSeen::UC_BTService_SetPlayerIfSeen()
{
}

void UC_BTService_SetPlayerIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if(PlayerPawn == nullptr)
	{
		return;
	}

	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),PlayerPawn);
	}else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}

void UC_BTService_SetPlayerIfSeen::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UC_BTService_SetPlayerIfSeen::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
	
}
