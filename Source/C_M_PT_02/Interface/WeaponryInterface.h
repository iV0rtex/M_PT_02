#pragma once
#include "C_M_PT_02/Weapon/C_BaseWeapon.h"
#include "WeaponryInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UWeaponryInterface: public UInterface
{
	GENERATED_BODY()
};

class IWeaponryInterface
{    
	GENERATED_BODY()

public:
	virtual void SetWeapon(AC_BaseWeapon * BaseWeapon) = 0;
};
