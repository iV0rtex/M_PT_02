// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/C_ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AC_ShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
