// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

AInventoryItem* UPlayerInventory::GetItem(const int32 Key)
{
	if(!Items.IsValidIndex(Key))
	{
		return nullptr;
	}
	return Items[Key];
}

void UPlayerInventory::SetItem(AInventoryItem* Item)
{
	
	Items.AddUnique(Item);
}

TArray<AInventoryItem*> UPlayerInventory::GetItems() const
{
	return Items;
}
