// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ShapeshifterActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangeColor);
DECLARE_DYNAMIC_DELEGATE(FOnMove);

UCLASS()
class C_M_PT_02_API AShapeshifterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShapeshifterActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent * BoxCollisionBody;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent * ShapeshifterBody;
	UFUNCTION()
	void MoveObject();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnChangeColor OnChangeColor;
	FOnMove OnMove;

};
