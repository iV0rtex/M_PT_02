#pragma once
#include "WeaponReloadInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UWeaponReloadInterface: public UInterface
{
	GENERATED_BODY()
	
};

class IWeaponReloadInterface
{    
	GENERATED_BODY()

public:
	virtual bool CanReload() = 0;
	virtual void Reload() = 0;
};
