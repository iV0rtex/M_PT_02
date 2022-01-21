// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ShooterPawn.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Controllers/C_ShooterAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "Weapon/C_PistolWeapon.h"
#include "Weapon/C_WeaponManagerComponent.h"

void AC_ShooterPawn::OnSeePawn(APawn* OtherPawn)
{
	auto* AIController = Cast<AC_ShooterAIController>(GetController());
	if(AIController)
	{

		AIController->GetBlackboardComponent()->ClearValue(TEXT("Noise"));
		AIController->GetBlackboardComponent()->SetValueAsObject(TEXT("Player"),OtherPawn);
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),OtherPawn->GetActorLocation());
		
		GetWorld()->GetTimerManager().SetTimer(SeeTimeHandle,this,&ThisClass::CantSeePawn,SeeTime,false);
	}
}

void AC_ShooterPawn::CantSeePawn()
{
	auto* AIController = Cast<AC_ShooterAIController>(GetController());
	if(AIController)
	{
		AIController->GetBlackboardComponent()->ClearValue(TEXT("Player"));
	}
}

void AC_ShooterPawn::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	const FString VolumeDes = FString::Printf(TEXT(" at volume %f"), Volume );
	FString Message = TEXT("Heard actor ") + OtherActor->GetName() + VolumeDes;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,Message);
	auto* AIController = Cast<AC_ShooterAIController>(GetController());
	if(AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("Noise"),Location);
	}
	
}

AC_ShooterPawn::AC_ShooterPawn()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensingComponent->SetPeripheralVisionAngle(90.f);
	SeeTime = .6f;
	
}

void AC_ShooterPawn::BeginPlay()
{
	Super::BeginPlay();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ThisClass::OnSeePawn);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &ThisClass::OnHearNoise);
	
	/*const FVector Position = this->GetActorLocation();
	const FRotator Rotation;
	AC_PistolWeapon * NewWeapon = GetWorld()->SpawnActor<AC_PistolWeapon>(Position,Rotation);
	SetWeapon(NewWeapon);*/
	
}

void AC_ShooterPawn::Shoot() const
{
	if(GetWeaponManager())
	{
		GetWeaponManager()->InteractCurrentWeapon();
	}
}

