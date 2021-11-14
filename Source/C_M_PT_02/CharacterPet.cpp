// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPet.h"

#include "C_M_PT_02Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACharacterPet::ACharacterPet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void ACharacterPet::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor *> Characters;
	UGameplayStatics::GetAllActorsOfClass(this,AC_M_PT_02Character::StaticClass(),Characters);
	for(AActor * CharacterActor : Characters)
	{
		AC_M_PT_02Character * Character = Cast<AC_M_PT_02Character>(CharacterActor);
		if(Character)
		{
			Character->OnDied.AddUFunction(this,"Die");
			Character->OnTookDamage.AddUFunction(this,"TookDamage");

			Health = Character->GetHealth();
			MaxHealth = Character->GetMaxHealth();
			break;
		}
		
	}
	OnDestroy.AddUFunction(this,"PrintDestroyStatus");
	OnTookDamage.AddUFunction(this,"PrintTookDamage");
	
}

void ACharacterPet::Die()
{
	if(OnDestroy.IsBound())
	{
		OnDestroy.Broadcast();
	}
	Destroy();
}

void ACharacterPet::TookDamage(const float Damage )
{
	Health -= Damage;
	if(Health < 0)
	{
		Health = 0;
	}
	if(OnTookDamage.IsBound())
	{
		OnTookDamage.Broadcast(Damage);
	}
}

void ACharacterPet::PrintDestroyStatus() const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Your Pet Has been Died")));
}

void ACharacterPet::PrintTookDamage(const float Damage) const
{
	const FString Message = "Your Pet Got " + FString::SanitizeFloat(Damage) + " Damage";
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, Message);
}

// Called every frame
void ACharacterPet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

