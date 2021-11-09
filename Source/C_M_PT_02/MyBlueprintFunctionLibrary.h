#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API UMyBlueprintFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Define is a platform android type */
	UFUNCTION(BlueprintCallable, Category="Definer",BlueprintPure)
	static bool IsAndroid();
	
};
