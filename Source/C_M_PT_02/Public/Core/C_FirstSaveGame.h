// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "C_FirstSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UC_FirstSaveGame : public USaveGame
{
	GENERATED_BODY()

	

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UC_FirstSaveGame();

public:
	UPROPERTY(VisibleAnywhere, Category=Basic)
	float PlayerHealth;
	UPROPERTY(VisibleAnywhere, Category=Basic)
	FVector PlayerPosition;
	
};
