#include "C_BaseWeapon.h"

#include "Components/BoxComponent.h"
#include "C_M_PT_02/Interface/WeaponryInterface.h"

AC_BaseWeapon::AC_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

}

void AC_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	this->SetReplicates(true);
	this->SetReplicateMovement(true);
	
}

void AC_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BaseWeapon::InteractWeapon()
{
	
}

void AC_BaseWeapon::OnOverlap(AActor* OtherActor)
{
	IWeaponryInterface * WeaponryActor = Cast<IWeaponryInterface>(OtherActor);
	if(WeaponryActor)
	{
		WeaponryActor->SetWeapon(this);
	}
}

void AC_BaseWeapon::OnDrop()
{
	
}

