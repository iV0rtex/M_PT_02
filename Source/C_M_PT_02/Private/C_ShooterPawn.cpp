// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ShooterPawn.h"

#include "Weapon/C_PistolWeapon.h"
#include "Weapon/C_WeaponManagerComponent.h"

AC_ShooterPawn::AC_ShooterPawn()
{
	
	
}

void AC_ShooterPawn::BeginPlay()
{
	Super::BeginPlay();
	
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

