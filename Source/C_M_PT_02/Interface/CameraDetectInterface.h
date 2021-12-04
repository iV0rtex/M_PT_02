#pragma once
#include "CameraDetectInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCameraDetectableInterface : public UInterface
{
	GENERATED_BODY()
	
};

class ICameraDetectableInterface
{    
	GENERATED_BODY()

public:
	//Camera see an object
	virtual void CameraTryToDetect(AActor * Detector) = 0;
	//Camera has lost an object
	virtual void CameraLost(AActor * Detector) = 0;
};

