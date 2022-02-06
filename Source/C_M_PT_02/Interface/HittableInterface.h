#pragma once
#include "HittableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UHittableInterface: public UInterface
{
	GENERATED_BODY()
};

class IHittableInterface
{    
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	 virtual void OnHit();
};