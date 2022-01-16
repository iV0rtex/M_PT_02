#pragma once

#include "CoreMinimal.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "C_ShooterPawn.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API AC_ShooterPawn : public AC_M_PT_02Character
{
	GENERATED_BODY()
public:
	AC_ShooterPawn();
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void Shoot() const;
	
};
