// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_RocketBullet.h"

#include "Kismet/GameplayStatics.h"

void AC_RocketBullet::BeginPlay()
{
	Super::BeginPlay();
	if(GetNetMode() != NM_DedicatedServer)
	{
		OnDestroyBullet.BindDynamic(this,&AC_RocketBullet::DestroyBulletMulticast);
		OnDestroyed.Add(OnDestroyBullet);
	}
	
}

void AC_RocketBullet::DestroyBulletMulticast()
{
	if(GetNetMode() == NM_DedicatedServer)
	{
		return;
	}
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ParticleSystem,
		this->GetTransform(),
		true,
		EPSCPoolMethod::AutoRelease,
		true
	);
}
