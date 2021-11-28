// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "ActorWithStatus.generated.h"

DECLARE_EVENT(AActorWithStatus,FOnChangeStatus);

UENUM(BlueprintType)
enum class EStatus : uint8
{
		Fear = 0 UMETA(DisplayName = "FearStatus"),
		Anger = 1 UMETA(DisplayName = "AngerStatus"),
		Max
};

UCLASS()
class C_M_PT_02_API AActorWithStatus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorWithStatus();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float DamageAmount;

	UPROPERTY(EditAnywhere)
	UBoxComponent * BoxComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent * MeshComponent;

	UPROPERTY(EditAnywhere)
	EStatus Status;
	FTimerHandle StatusTimeHandle;
	float ChangeStatusRate;

	FOnChangeStatus OnChangeStatus;

	void ChangeStatus();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	
	
	

};
