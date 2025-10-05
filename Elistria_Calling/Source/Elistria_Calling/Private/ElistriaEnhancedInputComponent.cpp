// Fill out your copyright notice in the Description page of Project Settings.


#include "ElistriaEnhancedInputComponent.h"



void UElistriaEnhancedInputComponent::ClearAbilityBindings()
{
	for (int32 Handle : AbilityActionBindings)
	{
		RemoveBindingByHandle(Handle);
	}
	AbilityActionBindings.Empty();
}
