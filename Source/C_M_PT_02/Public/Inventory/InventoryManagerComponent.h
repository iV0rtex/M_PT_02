#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_M_PT_02_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryManagerComponent();

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	TMap<AInventoryItem*, int32> MapItem;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server,BlueprintCallable,Reliable)
	void ServerAddItem(AInventoryItem* NewItem, int32 CountItem);
	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void ServerUseItem(AInventoryItem* SelectItem);
	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void ServerUseFirstItem();
	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void ServerDropItem(AInventoryItem* SelectItem, int32 CountItem);
	UFUNCTION(Server,BlueprintCallable,Unreliable)
	void ServerDropFirstItem();
	
};
