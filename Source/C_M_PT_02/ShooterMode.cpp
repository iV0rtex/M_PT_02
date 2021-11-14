// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMode.h"

#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void AShooterMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor *> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(this,ATurret::StaticClass(),TurretActors);
	for(AActor * TurretActor : TurretActors)
	{
		ATurret * Turret = Cast<ATurret>(TurretActor);
		if(Turret)
		{
			Turret->OnTurretKilled.AddUFunction(this,"OnTurretKilled");	
		}
		
	}
}

void AShooterMode::OnTurretKilled()
{
	Scores += 50.f;
}
