// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

bool UMyBlueprintFunctionLibrary::IsAndroid()
{
#if PLATFORM_ANDROID
	return true;
#endif
	return false;
}
