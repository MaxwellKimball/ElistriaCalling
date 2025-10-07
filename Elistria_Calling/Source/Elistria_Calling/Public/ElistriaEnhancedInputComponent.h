// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "PlayerGameplayAbilitiesDataAsset.h"
#include "ElistriaEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ELISTRIA_CALLING_API UElistriaEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass>
	void BindAbilityActionsByTag(const UPlayerGameplayAbilitiesDataAsset* InputConfig, UserClass* Object,
	                             void (UserClass::*Func)(const FInputActionInstance&, FGameplayTag));
	UFUNCTION(BlueprintCallable, Category="Input")
	void ClearAbilityBindings();

private:

	TArray<int32> AbilityActionBindings;
};
template <class UserClass>
void UElistriaEnhancedInputComponent::BindAbilityActionsByTag(const UPlayerGameplayAbilitiesDataAsset* InputConfig, UserClass* Object, void (UserClass::*Func)(const FInputActionInstance&, FGameplayTag))
{
	if (!InputConfig||!Func) return;

	static const ETriggerEvent EventsToBind[]={
		ETriggerEvent::Started,
		ETriggerEvent::Completed,
		ETriggerEvent::Canceled,
		ETriggerEvent::Triggered,
		ETriggerEvent::Ongoing
	};
	for (const FGameplayInputAbilityInfo& Info : InputConfig->AbilityMappings)
	{
		if (!Info.IsValid()) continue;

		for (ETriggerEvent Event : EventsToBind)
		{
			FEnhancedInputActionEventBinding& Binding = BindAction(Info.InputAction,Event,Object,Func,Info.InputTag);
			AbilityActionBindings.Add(Binding.GetHandle());
		}
	}
	{
		
	}
}

