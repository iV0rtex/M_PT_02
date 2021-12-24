// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeshifterActor.h"

// Sets default values
AShapeshifterActor::AShapeshifterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollisionBody = CreateDefaultSubobject<UBoxComponent>("BodyCollision");
	SetRootComponent(BoxCollisionBody);
	ShapeshifterBody = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	ShapeshifterBody->SetupAttachment(BoxCollisionBody);
}

// Called when the game starts or when spawned
void AShapeshifterActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollisionBody->OnComponentBeginOverlap.AddDynamic(this,&AShapeshifterActor::OnComponentBeginOverlap);
	OnMove.BindDynamic(this,&AShapeshifterActor::MoveObject);
	OnChangeColor.Add(OnMove);
}

void AShapeshifterActor::MoveObject()
{
	FVector Vector = GetActorLocation();
	Vector.X = Vector.X + 100;
	SetActorLocation(Vector);
}

void AShapeshifterActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OnChangeColor.IsBound())
	{
		OnChangeColor.Broadcast();
	}
	
}

// Called every frame
void AShapeshifterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

