#pragma once

#include "CoreMinimal.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

UCLASS()
class C_M_PT_02_API AInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AInventoryItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UBoxComponent* BoxCollision;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void InteractItem(AC_M_PT_02Character* Character);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	float DistanceDrop;

};
