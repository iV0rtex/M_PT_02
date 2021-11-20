// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnWithCamera.generated.h"

UCLASS()
class C_M_PT_02_API APawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnWithCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USpringArmComponent * SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent * CameraComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent * StaticMeshComp;
	UPROPERTY(EditAnywhere)
	float PawnSpeed;
	
	FVector MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;
	bool bJump;
	float JumpPower;
	float CurrentJumpPower;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void TurnCamera(float AxisValue);
	void LookUpCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	void Jump();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
