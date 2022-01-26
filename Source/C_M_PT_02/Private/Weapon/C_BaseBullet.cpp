
#include "Weapon/C_BaseBullet.h"

#include "Components/SphereComponent.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void AC_BaseBullet::SetDestroyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DestroyTimeHandle,this,&AC_BaseBullet::ServerDestroyBullet,TimeToDestroy);
}

void AC_BaseBullet::ServerDestroyBullet_Implementation()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(DestroyTimeHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(DestroyTimeHandle);
	}
	Destroy();
}

AC_BaseBullet::AC_BaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = CollisionComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	if(!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	TimeToDestroy = 5.f;
	SetReplicates(true);

}


void AC_BaseBullet::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		//UKismetSystemLibrary::PrintString(this,TEXT("HELLO"));
		SetDestroyTimer();
	}
}

void AC_BaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BaseBullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if(HasAuthority() && !Cast<AC_BaseBullet>(OtherActor))
	{
		ServerDestroyBullet();
	}
}

