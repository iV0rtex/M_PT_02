// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryV2.h"

// Sets default values for this component's properties
UPlayerInventoryV2::UPlayerInventoryV2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MaxXItems = 6;
	MaxYItems = 6;
}


// Called when the game starts
void UPlayerInventoryV2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventoryV2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UItemInventoryV2* UPlayerInventoryV2::GetItem(const int32 Key)
{
	if(!Items.IsValidIndex(Key))
	{
		return nullptr;
	}
	return Items[Key];
}

void UPlayerInventoryV2::SetItem(UItemInventoryV2* Item)
{
	if(Items.Num() < (MaxXItems*MaxYItems))
	{
		Items.AddUnique(Item);
	}
}

TArray<UItemInventoryV2*> UPlayerInventoryV2::GetItems() const
{
	return Items;
}

