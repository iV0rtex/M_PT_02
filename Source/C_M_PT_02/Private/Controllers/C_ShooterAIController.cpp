// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/C_ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

FGenericTeamId AC_ShooterAIController::GetGenericTeamId() const
{
	return FGenericTeamId(1);
}

AC_ShooterAIController::AC_ShooterAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

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
