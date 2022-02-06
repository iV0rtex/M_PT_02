// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "ActorWithStatus.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterMode.generated.h"

/**
 * 
 */
UCLASS()
class C_M_PT_02_API AShooterMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterMode();

protected:
	virtual void BeginPlay() override;

	void GenerateCubes();
	void DestroyCubes();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY()
	TArray<AActorWithStatus*> GeneratedActors;

	ATargetPoint * GetFirstTargetPoint() const; 
	ATargetPoint * GetSecondTargetPoint() const;
	ATargetPoint * GetTargetPointByTagName(FName Name) const;
	FVector GetRandomPosition() const;
	FTimerHandle GeneratedActorsLifeTimeHandle;

public:
	float Scores;
	
	UFUNCTION()
	void OnTurretKilled();

	UFUNCTION(BlueprintCallable, Category="UGM Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax = "100", UIMin = "1", UIMax = "100"))
	int32 GeneratedCubeAmount;
	float GeneratedActorsLifeTime;
	
};
