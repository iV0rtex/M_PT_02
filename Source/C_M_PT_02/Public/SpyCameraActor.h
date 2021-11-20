// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "SpyCameraActor.generated.h"

DECLARE_EVENT(ASpyCameraActor, FOnPlayerDetected);
DECLARE_EVENT(ASpyCameraActor, FOnPlayerGone);

/**
 * 
 */
UCLASS()
class C_M_PT_02_API ASpyCameraActor : public ACameraActor
{
	GENERATED_BODY()
public:
	ASpyCameraActor();
	virtual void BeginPlay() override;
	
	FOnPlayerDetected OnPlayerDetected;
	FOnPlayerGone OnPlayerGone;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent * BoxComp;

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void PlayerDetected();
	UFUNCTION()
	void PlayerGone();

	void DetectionTimerAction();
	void LoosingTimerAction();

	FTimerHandle DetectTimeHandle;
	FTimerHandle LossTimeHandle;
	bool bIsPlayerDetected;

	UPROPERTY(VisibleAnywhere)
	float DetectTime;
	UPROPERTY(VisibleAnywhere)
	float LoosTime;
	
};
