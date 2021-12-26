#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseWeapon.generated.h"

class UBoxComponent;
UCLASS()
class C_M_PT_02_API AC_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;
	
public:	
	AC_BaseWeapon();

	UStaticMeshComponent* GetStaticMeshComponent() const { return  StaticMeshComponent; }
	UBoxComponent* GetBoxComponent() const { return  BoxComponent; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;
	
	virtual void InteractWeapon();

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* OtherActor);
	UFUNCTION(BlueprintCallable)
	virtual void OnDrop();

};
