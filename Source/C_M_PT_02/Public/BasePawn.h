// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "C_M_PT_02/Interface/CameraDetectInterface.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDetectedColor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDefaultColor);
DECLARE_EVENT(ABasePawn,FOnTookDamage);
DECLARE_EVENT(ABasePawn, FOnCameraDetected);
DECLARE_EVENT(ABasePawn, FOnDetectionGone);

USTRUCT(BlueprintType)
struct FSHealth
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float Health;	
};

UCLASS()
class C_M_PT_02_API ABasePawn : public APawn,public ICameraDetectableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent * SphereComponent;
	UPROPERTY(VisibleAnywhere)
	UPawnMovementComponent * MovementComponent;

	

	void MoveForward(float Val);
	void MoveRight(float Val);
	UFUNCTION()
	void SetPlayerDetectedStatus();
	UFUNCTION()
	void UnsetPlayerDetectedStatus();
	UFUNCTION()
	void PrintHealth() const;
	
	
	FSHealth SHealth;

	FTimerHandle DetectTimeHandle;
	FTimerHandle LossTimeHandle;
	bool bIsDetected;

	UPROPERTY(VisibleAnywhere)
	float DetectTime;
	UPROPERTY(VisibleAnywhere)
	float LoosTime;

	FOnCameraDetected OnCameraDetected;
	FOnDetectionGone OnDetectionGone;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	AActor * WatchThroughActor;

	UPROPERTY(BlueprintAssignable)
	FOnDetectedColor OnDetectedColor;
	UPROPERTY(BlueprintAssignable)
	FOnDefaultColor OnDefaultColor;

	FOnTookDamage OnTookDamage;

	void Damage( float Damage);
	virtual void CameraTryToDetect(AActor* Detector) override;
	virtual void CameraLost(AActor* Detector) override;
	UFUNCTION()
	void PlayerDetected();
	UFUNCTION()
	void PlayerGone();

	void DetectionTimerAction();
	void LoosingTimerAction();

};
