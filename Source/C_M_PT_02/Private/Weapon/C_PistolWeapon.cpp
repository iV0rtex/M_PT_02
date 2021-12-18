// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_PistolWeapon.h"

AC_PistolWeapon::AC_PistolWeapon()
{
	bCanFire = true;
	FireDuration = .6f;
}

void AC_PistolWeapon::EndFire_Implementation()
{
	bCanFire = true;
}

bool AC_PistolWeapon::CanFire() const
{
	return Super::CanFire() && bCanFire;
}

void AC_PistolWeapon::InteractWeapon()
{
	if (!CanFire())
	{
		return;
	}
	UseAmmo();
	Fire();
	bCanFire = false;
	GetWorld()->GetTimerManager().SetTimer(FireTimeHandle,this,&AC_PistolWeapon::EndFire,FireDuration);
}