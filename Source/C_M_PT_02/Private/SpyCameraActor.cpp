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

	DetectTime = 5.f;
	LoosTime = 10.f;
	bIsPlayerDetected = false;
	
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
	APlayerController * PC = GetWorld()->GetFirstPlayerController();

	APawn * Pawn = PC->GetPawn();
	ABasePawn * BPawn = Cast<ABasePawn>(Pawn);
	if(!BPawn)
	{
		return;
	}
	BPawn->WatchThroughActor = this;

	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.f;
	
	DetectionTimerAction();
	
	PC->SetViewTarget(this,TransitionParams);
}

void ASpyCameraActor::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerController * PC = GetWorld()->GetFirstPlayerController();
	APawn * Pawn = PC->GetPawn();
	ABasePawn * BPawn = Cast<ABasePawn>(Pawn);
	if(!BPawn)
	{
		return;
	}
	BPawn->WatchThroughActor = BPawn;

	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 2.f;

	LoosingTimerAction();
	
	PC->SetViewTarget(PC->GetPawn(),TransitionParams);
}
void ASpyCameraActor::PlayerDetected()
{
	bIsPlayerDetected = true;
	OnPlayerDetected.Broadcast();
	
}
void ASpyCameraActor::PlayerGone()
{
	bIsPlayerDetected = false;
	OnPlayerGone.Broadcast();
}

void ASpyCameraActor::DetectionTimerAction()
{
	if(GetWorldTimerManager().IsTimerActive(LossTimeHandle))
	{
		GetWorldTimerManager().ClearTimer(LossTimeHandle);
	}
	if(!bIsPlayerDetected)
	{
		GetWorld()->GetTimerManager().SetTimer(DetectTimeHandle,this,&ASpyCameraActor::PlayerDetected,DetectTime,false);
	}
}

void ASpyCameraActor::LoosingTimerAction()
{
	if(GetWorldTimerManager().IsTimerActive(DetectTimeHandle))
	{
		GetWorldTimerManager().ClearTimer(DetectTimeHandle);
	}
	if(bIsPlayerDetected)
	{
		GetWorld()->GetTimerManager().SetTimer(LossTimeHandle,this,&ASpyCameraActor::PlayerGone,LoosTime,false);
	}
}
