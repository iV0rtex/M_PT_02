// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMode.h"

#include "Turret.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AShooterMode::AShooterMode()
{
	GeneratedCubeAmount = 5;
	GeneratedActorsLifeTime = 5.f;
}

void AShooterMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor *> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(this,ATurret::StaticClass(),TurretActors);
	for(AActor * TurretActor : TurretActors)
	{
		ATurret * Turret = Cast<ATurret>(TurretActor);
		if(Turret)
		{
			Turret->OnTurretKilled.AddUFunction(this,"OnTurretKilled");	
		}
	}

	GenerateCubes();
	GetWorld()->GetTimerManager().SetTimer(GeneratedActorsLifeTimeHandle,this,&ThisClass::DestroyCubes,GeneratedActorsLifeTime,false);

	ChangeMenuWidget(StartingWidgetClass);

	AssetsLoading();
	
}

void AShooterMode::GenerateCubes()
{
	const int32 GCubeAmount = FMath::Clamp<float>(GeneratedCubeAmount,1,100);
	for(int32 i = 0 ; i < GCubeAmount; i++)
	{
		FVector Position = GetRandomPosition();
		FRotator Rotation;
		AActorWithStatus * NewActor = GetWorld()->SpawnActor<AActorWithStatus>(Position,Rotation);
		
		GeneratedActors.Add(NewActor);
	}
}

void AShooterMode::DestroyCubes()
{
	for(AActorWithStatus * GeneratedActor : GeneratedActors)
	{
		GeneratedActor->Destroy();
	}
	GeneratedActors.Empty();
}

ATargetPoint* AShooterMode::GetFirstTargetPoint() const
{
	return GetTargetPointByTagName(TEXT("firstLocation"));
}

ATargetPoint* AShooterMode::GetSecondTargetPoint() const
{
	return GetTargetPointByTagName(TEXT("secondLocation"));
}

ATargetPoint* AShooterMode::GetTargetPointByTagName(const FName Name) const
{
	TArray<AActor *> TargetActors;
	ATargetPoint * TargetPoint = nullptr;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ATargetPoint::StaticClass(),Name,TargetActors);
	for (AActor * TargetActor : TargetActors)
	{
		TargetPoint = Cast<ATargetPoint>(TargetActor);
	}
	return TargetPoint;
}

FVector AShooterMode::GetRandomPosition() const
{
	FVector Position;
	ATargetPoint * FirstTargetPoint = GetFirstTargetPoint();
	ATargetPoint * SecondTargetPoint = GetSecondTargetPoint();
	if(!FirstTargetPoint || !SecondTargetPoint)
	{
		return Position;
	}
	
	FVector FirstPointLocation  = FirstTargetPoint->GetActorLocation();
	FVector SecondPointLocation  = SecondTargetPoint->GetActorLocation();

	Position.X = UKismetMathLibrary::RandomFloatInRange(FirstPointLocation.X,SecondPointLocation.X);
	Position.Y = UKismetMathLibrary::RandomFloatInRange(FirstPointLocation.Y,SecondPointLocation.Y);
	Position.Z = FirstPointLocation.Z;

	return Position;
}

void AShooterMode::AssetsLoading()
{
	TArray<FSoftObjectPath> AsyncItemsToStream;
	TArray<FSoftObjectPath> SyncItemsToStream;
	
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	AsyncItemsToStream.Add(ThirdAsyncSoftObject.ToSoftObjectPath());
	AsyncItemsToStream.Add(ForthAsyncSoftObject.ToSoftObjectPath());

	Streamable.RequestAsyncLoad(AsyncItemsToStream, FStreamableDelegate::CreateUObject(this, &AShooterMode::AssetsLoaded));

	Streamable.RequestSyncLoad(SyncItemsToStream);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Sync Asset Loaded"));
}

void AShooterMode::AssetsLoaded()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("ASync Asset Loaded"));
}

void AShooterMode::OnTurretKilled()
{
	Scores += 50.f;
}

void AShooterMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if(CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if(NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if(CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
