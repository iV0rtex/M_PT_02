#include "Inventory/InventoryItem.h"

#include "Components/BoxComponent.h"

AInventoryItem::AInventoryItem()
{
	PrimaryActorTick.bCanEverTick = true;
	DistanceDrop = 300.f;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	this->SetReplicates(true);
	this->SetReplicateMovement(true);
	
}

void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryItem::InteractItem(AC_M_PT_02Character* Character)
{
	
}

void AInventoryItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AC_M_PT_02Character* Character = Cast<AC_M_PT_02Character>(OtherActor);
	if(IsValid(Character))
	{
		Character->GetItem(this);
		this->SetActorHiddenInGame(true);
		this->BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

