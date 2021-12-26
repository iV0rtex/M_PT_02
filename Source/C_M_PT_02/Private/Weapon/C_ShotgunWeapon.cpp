// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_ShotgunWeapon.h"

#include "DrawDebugHelpers.h"
#include "C_M_PT_02/C_M_PT_02Character.h"
#include "Kismet/KismetMathLibrary.h"

AC_ShotgunWeapon::AC_ShotgunWeapon()
{
	AmmoPerClip = 1;
	CurrentAmmoInClip = AmmoPerClip;
	BulletAmount = 6;
	Range = 1000;
}

void AC_ShotgunWeapon::LaunchBullet_Implementation()
{
	for(int32 i = 0; i<BulletAmount;i++)
	{
		FVector LocationSocket = GetStaticMeshComponent()->GetSocketLocation("Muzzle");
		FCollisionQueryParams RV_TraceParams;
		RV_TraceParams.bTraceComplex = true;
		FHitResult RV_Hit(ForceInit);
		FVector LocationEnd = LocationSocket;
		FVector Forward = this->GetActorForwardVector();
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle working %s"), *Forward.ToString());
		Forward = Forward * Range;
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle working %s"), *Forward.ToString());
		Forward.Z += UKismetMathLibrary::RandomIntegerInRange(-200,200);
		Forward.Y += UKismetMathLibrary::RandomIntegerInRange(-200,200);
		LocationEnd += Forward;
		GetWorld()->LineTraceSingleByChannel(
		   RV_Hit,
		   LocationSocket,
		   LocationEnd,
		   ECC_Pawn,
		   RV_TraceParams
		);
		DrawDebugLine(
		   GetWorld(),
		   LocationSocket,
		   LocationEnd,
		   FColor(255, 0, 0),
		   false,
		   0.3,
		   0,
		   2
		   );
		if (RV_Hit.bBlockingHit)
		{
			auto* Character = Cast<AC_M_PT_02Character>(RV_Hit.GetActor());
			if (Character)
			{
				//Character->ApplyDamage(Damage); //TODO: for the future updates
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RV_Hit.GetActor()->GetName());
		}
	}
	
}


