// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithCamera.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//Attach components
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(StaticMeshComp);
	CameraComp->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);

	//Assign SpringArm class variables.
	SpringArmComponent->SetRelativeLocationAndRotation(FVector(0.f,0.f,50.f),FRotator(-60.f,0.f,0.f));
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 3.f;
	PawnSpeed = 500.f;
	JumpPower = 300.f;
	CurrentJumpPower = 0.f;

	//Take control of the default player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
}

void APawnWithCamera::MoveForward(const float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue,-1.f,1.f);
}

void APawnWithCamera::MoveRight(const float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.f,1.f);
}

void APawnWithCamera::TurnCamera(const float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw	+= AxisValue;
	SetActorRotation(NewRotation);
}

void APawnWithCamera::LookUpCamera(const float AxisValue)
{
	FRotator NewRotation = SpringArmComponent->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch-AxisValue,-80.f,0.f);
	SpringArmComponent->SetWorldRotation(NewRotation);
	
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}

void APawnWithCamera::Jump()
{
	if(CurrentJumpPower == 0.f)
	{
		bJump = true;
	}
	
}

// Called every frame
void APawnWithCamera::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	{
		if(bZoomingIn)
		{
			ZoomFactor += DeltaTime/.5f;
		}else
		{
			ZoomFactor -= DeltaTime/.25f;
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor,0.f,1.f);
		
		CameraComp->FieldOfView = FMath::Lerp<float>(90.f,60.f,ZoomFactor);
		SpringArmComponent->TargetArmLength = FMath::Lerp<float>(400.f,300.f,ZoomFactor);
	}
	
	{
		if(!MovementInput.IsZero())
		{
			MovementInput = MovementInput.GetSafeNormal() * PawnSpeed;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
		
		if(bJump)
		{
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorUpVector() * PawnSpeed * DeltaTime;
			CurrentJumpPower += GetActorUpVector().Z * PawnSpeed * DeltaTime;
			SetActorLocation(NewLocation);
			
			if(CurrentJumpPower >= JumpPower)
			{
				bJump = false;
			}
		}else if(CurrentJumpPower > 0.f)
		{
			FVector NewLocation = GetActorLocation();
			NewLocation -= GetActorUpVector() * PawnSpeed * DeltaTime;
			CurrentJumpPower -= GetActorUpVector().Z * PawnSpeed * DeltaTime;
			SetActorLocation(NewLocation);
			
			CurrentJumpPower = FMath::Clamp<float>(CurrentJumpPower,0.f,JumpPower);
		}
	}

}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APawnWithCamera::Jump);
	InputComponent->BindAxis("MoveForward",this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight",this,&APawnWithCamera::MoveRight);
	InputComponent->BindAxis("Turn",this,&APawnWithCamera::TurnCamera);
	InputComponent->BindAxis("LookUp",this,&APawnWithCamera::LookUpCamera);

}

