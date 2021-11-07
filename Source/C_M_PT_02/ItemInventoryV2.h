// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInventoryV2.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UItemInventoryV2 : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 ID;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString Name;
	
};
