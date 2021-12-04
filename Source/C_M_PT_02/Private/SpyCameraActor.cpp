// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyCameraActor.h"

#include "BasePawn.h"

ASpyCameraActor::ASpyCameraActor()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(500.f));
	BoxComp->SetCollisionObjectType(ECC_WorldStatic);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	BoxComp->SetupAttachment(GetRootComponent());
	
}

void ASpyCameraActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&ASpyCameraActor::BoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this,&ASpyCameraActor::BoxEndOverlap);
	
}

void ASpyCameraActor::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ICameraDetectableInterface * DetectablePawn = Cast<ICameraDetectableInterface>(OtherActor);
	
	ICameraDetectableInterface * DetectableController = Cast<ICameraDetectableInterface>(OtherActor->GetInstigatorController());
	if(DetectablePawn)
	{
		DetectablePawn->CameraTryToDetect(this);
	}
	if(DetectableController)
	{
		DetectableController->CameraTryToDetect(this);
	}
}

void ASpyCameraActor::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ICameraDetectableInterface * DetectablePawn = Cast<ICameraDetectableInterface>(OtherActor);
	
	ICameraDetectableInterface * DetectableController = Cast<ICameraDetectableInterface>(OtherActor->GetInstigatorController());
	if(DetectablePawn)
	{
		DetectablePawn->CameraLost(this);
	}
	if(DetectableController)
	{
		DetectableController->CameraLost(this);
	}
}



