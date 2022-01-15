#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseBullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

DECLARE_DYNAMIC_DELEGATE(FDestroyBullet);

UCLASS()
class C_M_PT_02_API AC_BaseBullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	void SetDestroyTimer();
	FTimerHandle DestroyTimeHandle;
	
	UFUNCTION(Server,Unreliable)
	void ServerDestroyBullet();
	
public:	
	AC_BaseBullet();
	
	FDestroyBullet OnDestroyBullet;

protected:
	float TimeToDestroy;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
