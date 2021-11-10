// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemInventoryV2.h"
#include "PlayerInventoryV2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_M_PT_02_API UPlayerInventoryV2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventoryV2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TArray<UItemInventoryV2*> Items;
public:
	UPROPERTY(BlueprintReadWrite,Category="Items",EditAnywhere)
	int32 MaxXItems;
	UPROPERTY(BlueprintReadWrite,Category="Items",EditAnywhere)
	int32 MaxYItems;
	
	UFUNCTION(BlueprintCallable)
	UItemInventoryV2* GetItem(const int32 Key);

	UFUNCTION(BlueprintCallable)
	void SetItem(UItemInventoryV2* Item);

	UFUNCTION(BlueprintCallable)
	TArray<UItemInventoryV2*> GetItems() const;

		
};
