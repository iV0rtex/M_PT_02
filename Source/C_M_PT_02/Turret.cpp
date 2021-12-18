// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBody = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	SetRootComponent(TurretBody);
	Health = 100.f;
	LifeTime = 10.f;
}

void ATurret::BeginDestroy()
{
	Super::BeginDestroy();

	if(OnTurretKilled.IsBound())
	{
		OnTurretKilled.Broadcast();
	}
}

void ATurret::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Health -= 15.f;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	//TurretBody->OnComponentHit.AddDynamic(this,&ATurret::OnComponentHit);

	GetWorld()->GetTimerManager().SetTimer(LifeTimeHandle,this,&ATurret::Die,LifeTime,false);
	OnDestroy.AddUFunction(this,"PrintDestroyStatus");
}
void ATurret::Die()
{
	if(OnDestroy.IsBound())
	{
		OnDestroy.Broadcast();
	}
	Destroy();
}

void ATurret::PrintDestroyStatus() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Turret Has been Destroyed")));
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

