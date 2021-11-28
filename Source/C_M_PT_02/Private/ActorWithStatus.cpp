// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWithStatus.h"

#include "BasePawn.h"
#include "StaticMeshAttributes.h"

// Sets default values
AActorWithStatus::AActorWithStatus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ChangeStatusRate = 1.f;
	Status = EStatus::Anger;
	DamageAmount = 2.f;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetBoxExtent(FVector(50.f));
	BoxComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if(DefaultMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(DefaultMesh.Object);
	}
}

// Called when the game starts or when spawned
void AActorWithStatus::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(StatusTimeHandle,this,&ThisClass::ChangeStatus,ChangeStatusRate,true);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnComponentBeginOverlap);
	
}

// Called every frame
void AActorWithStatus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorWithStatus::ChangeStatus()
{
	if(Status == EStatus::Anger)
	{
		Status = EStatus::Fear;
	}else
	{
		Status = EStatus::Anger;
	}

	OnChangeStatus.Broadcast();
}

void AActorWithStatus::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABasePawn * Pawn = Cast<ABasePawn>(OtherActor);
	if(Pawn)
	{
		Pawn->Damage(DamageAmount);
	}
}

