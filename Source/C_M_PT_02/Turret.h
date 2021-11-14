// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

DECLARE_EVENT(ATurret,FOnTurretKilled);
DECLARE_EVENT(ATurret,FOnDestroy);

UCLASS()
class C_M_PT_02_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	float Health;

	UPROPERTY(Transient)
	UStaticMeshComponent * TurretBody;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	void OnComponentHit(UPrimitiveComponent * HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float LifeTime;
	FOnDestroy	OnDestroy;
	FTimerHandle LifeTimeHandle;

	void Die();
	UFUNCTION()
	void PrintDestroyStatus() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnTurretKilled OnTurretKilled;

};


