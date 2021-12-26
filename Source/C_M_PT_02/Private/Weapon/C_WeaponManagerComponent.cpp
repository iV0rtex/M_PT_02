// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_WeaponManagerComponent.h"

#include "Components/BoxComponent.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UC_WeaponManagerComponent::UC_WeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DistanceToDropWeapon = 100;

	// ...
}


// Called when the game starts
void UC_WeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_WeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UC_WeaponManagerComponent::SetCurrentWeapon_Implementation(AC_BaseWeapon* NewWeapon)
{
	/*if(!GetOwner()->HasAuthority())
	{
		return false;
	}*///TODO: Fix it
	if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
		auto* Character = Cast<AC_M_PT_02Character>(GetOwner());
		const FAttachmentTransformRules Rules = FAttachmentTransformRules::KeepRelativeTransform;
		CurrentWeapon->AttachToActor(Character, Rules, FName(TEXT("SocketWeapon")));
		CurrentWeapon->SetActorRelativeLocation(FVector{50,0,20});
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UC_WeaponManagerComponent::DropCurrentWeapon_Implementation()
{
	/*if(!GetOwner()->HasAuthority())
	{
		return false;
	}*///TODO: Fix it
	if(CurrentWeapon)
	{
		CurrentWeapon->SetOwner(nullptr);
		const FDetachmentTransformRules Rules = FDetachmentTransformRules::KeepRelativeTransform;
		CurrentWeapon->DetachFromActor(Rules);
		CurrentWeapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		auto* Character = Cast<AC_M_PT_02Character>(GetOwner());
		const FVector NewLocation = Character->GetMesh()->GetRightVector() * DistanceToDropWeapon + Character->GetMesh()->GetComponentLocation();
		FHitResult* OutSweepHitResult = nullptr;
		CurrentWeapon->SetActorLocation(NewLocation,false,OutSweepHitResult,ETeleportType::None);
		CurrentWeapon->OnDrop();
		CurrentWeapon = nullptr;
	}
}

void UC_WeaponManagerComponent::InteractCurrentWeapon_Implementation()
{
	/*if(!GetOwner()->HasAuthority())
	{
		return false;
	}*///TODO: Fix it
	if(CurrentWeapon)
	{
		CurrentWeapon->InteractWeapon();
	}
}

void UC_WeaponManagerComponent::ReloadCurrentWeapon_Implementation()
{
	/*if(!GetOwner()->HasAuthority())
	{
		return false;
	}*///TODO: Fix it
	if(CurrentWeapon)
	{
		IWeaponReloadInterface *  WeaponReload = Cast<IWeaponReloadInterface>(CurrentWeapon);
		if(WeaponReload)
		{
			WeaponReload->Reload();
		}
	}
}

