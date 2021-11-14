// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterPet.generated.h"

DECLARE_EVENT(ACharacterPet,FOnDestroy);
DECLARE_EVENT_OneParam(ACharacterPet,FOnDamage,float);

UCLASS()
class C_M_PT_02_API ACharacterPet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterPet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	
	UFUNCTION()
	void Die();
	UFUNCTION()
	void TookDamage(const float Damage);
	UFUNCTION()
	void PrintDestroyStatus() const;
	UFUNCTION()
	void PrintTookDamage(const float Damage) const;

	float Health;
	float MaxHealth;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FOnDestroy	OnDestroy;
	FOnDamage	OnTookDamage;
	
};
