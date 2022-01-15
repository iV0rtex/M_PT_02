#include "Inventory/InventoryManagerComponent.h"

#include "Components/BoxComponent.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "Net/UnrealNetwork.h"

UInventoryManagerComponent::UInventoryManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UInventoryManagerComponent::ServerUseFirstItem_Implementation()
{
	TArray<AInventoryItem*> Keys;
	const int32 KeysAmount = MapItem.GetKeys(Keys);
	if (KeysAmount >0)
	{
		ServerUseItem(Keys[0]);
	}
}

void UInventoryManagerComponent::ServerAddItem_Implementation(AInventoryItem* NewItem, int32 CountItem)
{
	if(!GetOwner()->HasAuthority())
	{
		return;
	}
	if(MapItem.Find(NewItem) == nullptr)
	{
		MapItem.Add(NewItem,CountItem);
	}
}

void UInventoryManagerComponent::ServerUseItem_Implementation(AInventoryItem* SelectItem)
{
	AInventoryItem* Item = Cast<AInventoryItem>(SelectItem);
	if(Item)
	{
		AC_M_PT_02Character* Character = Cast<AC_M_PT_02Character>(GetOwner());
		auto* CurrentCount = MapItem.Find(SelectItem);
		if(Character)
		{
			if(*CurrentCount == 1)
			{
				MapItem.Remove(SelectItem);
			}else
			{
				CurrentCount -= 1;
			}
			Item->InteractItem(Character);
		}
	}
}


void UInventoryManagerComponent::ServerDropFirstItem_Implementation()
{
	TArray<AInventoryItem*> Keys;
	const int32 KeysAmount = MapItem.GetKeys(Keys);
	if (KeysAmount > 0)
	{
		ServerDropItem(Keys[0], *MapItem.Find(Keys[0]));
	}
}

void UInventoryManagerComponent::ServerDropItem_Implementation(AInventoryItem* SelectItem, int32 CountItem)
{
	AInventoryItem* Item = Cast<AInventoryItem>(SelectItem);
	auto* CurrentCount = MapItem.Find(SelectItem);
	if(CurrentCount != nullptr && *CurrentCount >= CountItem)
	{
		auto* Character = Cast<AC_M_PT_02Character>(GetOwner());
		for(int i=0;i< CountItem; i++)
		{
			const FVector NewLocation = Character->GetMesh()->GetRightVector() * SelectItem->DistanceDrop + Character->GetMesh()->GetComponentLocation();
			FHitResult* OutSweepHitResult = nullptr;
			SelectItem->SetActorLocation(NewLocation,false,OutSweepHitResult,ETeleportType::None);
			SelectItem->SetActorHiddenInGame(false);
			SelectItem->BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		*CurrentCount -= CountItem;
		if(*CurrentCount == 0)
		{
			MapItem.Remove(SelectItem);
		}
	}
}

