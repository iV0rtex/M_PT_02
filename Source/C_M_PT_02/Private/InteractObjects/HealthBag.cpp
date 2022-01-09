#include "InteractObjects/HealthBag.h"

AHealthBag::AHealthBag()
{
	Health = 10;
}

void AHealthBag::InteractItem(AC_M_PT_02Character* Character)
{
	Super::InteractItem(Character);
	Character->AddHealth(Health);
	
}
