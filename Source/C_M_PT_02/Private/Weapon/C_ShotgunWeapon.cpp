// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_ShotgunWeapon.h"

#include "DrawDebugHelpers.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "Kismet/KismetMathLibrary.h"

AC_ShotgunWeapon::AC_ShotgunWeapon()
{
	AmmoPerClip = 1;
	CurrentAmmoInClip = AmmoPerClip;
	BulletAmount = 6;
	Range = 1000;
}

void AC_ShotgunWeapon::ServerLaunchBullet_Implementation()
{
	const FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
	
	
	for(int32 i = 0; i<BulletAmount;i++)
	{
		FRotator Rotation = this->GetActorRotation();
		Rotation.Pitch += UKismetMathLibrary::RandomFloatInRange(-20.f,20.f);
		Rotation.Yaw += UKismetMathLibrary::RandomFloatInRange(-20.f,20.f);
		GetWorld()->SpawnActor(Bullet,&LocationSocket,&Rotation);
	}
	
}



