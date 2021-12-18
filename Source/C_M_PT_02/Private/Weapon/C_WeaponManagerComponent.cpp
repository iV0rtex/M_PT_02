// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_WeaponManagerComponent.h"

#include "C_M_PT_02/C_M_PT_02Character.h"

// Sets default values for this component's properties
UC_WeaponManagerComponent::UC_WeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

bool UC_WeaponManagerComponent::SetCurrentWeapon(AC_BaseWeapon* NewWeapon)
{
	if (!CurrentWeapon)
	{
		CurrentWeapon = NewWeapon;
		auto* Character = Cast<AC_M_PT_02Character>(GetOwner());
		const FAttachmentTransformRules Rules = FAttachmentTransformRules::KeepRelativeTransform;
		CurrentWeapon->AttachToActor(Character, Rules, FName(TEXT("SocketWeapon")));
		CurrentWeapon->SetActorRelativeLocation(FVector{50,0,20});
		CurrentWeapon->SetActorEnableCollision(false);
		return true;
	}
	return false;
}

void UC_WeaponManagerComponent::InteractCurrentWeapon()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->InteractWeapon();
	}
}

void UC_WeaponManagerComponent::ReloadCurrentWeapon()
{
	if(CurrentWeapon)
	{
		IWeaponReloadInterface *  WeaponReload = Cast<IWeaponReloadInterface>(CurrentWeapon);
		if(WeaponReload)
		{
			WeaponReload->Reload();
		}
	}
}

