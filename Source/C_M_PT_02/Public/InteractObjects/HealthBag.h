#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItem.h"
#include "HealthBag.generated.h"

UCLASS()
class C_M_PT_02_API AHealthBag : public AInventoryItem
{
	GENERATED_BODY()
public:
	AHealthBag();
	UFUNCTION(BlueprintCallable)
	virtual void InteractItem(AC_M_PT_02Character* Character) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Health;
};
