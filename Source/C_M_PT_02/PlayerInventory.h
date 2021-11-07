// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AInventoryItem;

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UPlayerInventory final : public UUserWidget
{
	GENERATED_BODY()

protected:
	TArray<AInventoryItem*> Items;
public:
	UFUNCTION(BlueprintCallable)
	AInventoryItem* GetItem(const int32 Key);

	UFUNCTION(BlueprintCallable)
	void SetItem(AInventoryItem* Item);

	UFUNCTION(BlueprintCallable)
	TArray<AInventoryItem*> GetItems() const;
};
