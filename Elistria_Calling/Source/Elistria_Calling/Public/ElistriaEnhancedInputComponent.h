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
	template<class UserClass, typename FuncType>
	void BindAbilityActions(const UPlayerGameplayAbilitiesDataAsset* InputConfig, UserClass* Object, FuncType Func);

	void ClearAbilityBindings();
	
private:

	TArray<uint32> AbilityActionBindings;
};
template<class UserClass, typename FuncType>
void UElistriaEnhancedInputComponent::BindAbilityActions(const UPlayerGameplayAbilitiesDataAsset* InputConfig, UserClass* Object, FuncType Func)
{
	if (!InputConfig) return;

	for (const FGameplayInputAbilityInfo& AbilityInfo : InputConfig->GetInputAbilities())
	{
		if (AbilityInfo.IsValid())
		{
			BindAction(AbilityInfo.InputAction,ETriggerEvent::Triggered,Object,Func,AbilityInfo.InputID);
		}
	}
}