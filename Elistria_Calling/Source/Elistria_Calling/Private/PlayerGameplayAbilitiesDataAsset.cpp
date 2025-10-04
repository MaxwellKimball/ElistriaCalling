// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameplayAbilitiesDataAsset.h"

UPlayerGameplayAbilitiesDataAsset::UPlayerGameplayAbilitiesDataAsset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Constructor implementation
}

const TSet<FGameplayInputAbilityInfo>& UPlayerGameplayAbilitiesDataAsset::GetInputAbilities() const
{
	return InputAbilities;
}

#if WITH_EDITOR
void UPlayerGameplayAbilitiesDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FProperty* Property = PropertyChangedEvent.Property;
	if (Property && Property->GetName()==GET_MEMBER_NAME_CHECKED(UPlayerGameplayAbilitiesDataAsset, InputAbilities)&& !InputAbilities.IsEmpty())
	{
		TArray<FGameplayInputAbilityInfo> InputAbilitiesArray = InputAbilities.Array();
		for (int32 i = InputAbilitiesArray.Num() - 1; i >= 0; i--)
		{
			const int32 PrevIndex = i - 1;
			if (InputAbilitiesArray[i]==InputAbilitiesArray[PrevIndex])
			{
				InputAbilitiesArray.RemoveAtSwap(i);
			}
		}
		InputAbilities.Reset();

		for (int32 i=0; i<InputAbilitiesArray.Num(); i++)
		{
			FGameplayInputAbilityInfo& AbilityInfo = InputAbilitiesArray[i];
			AbilityInfo.InputID = i;
			InputAbilities.Add(AbilityInfo);
		}
	}
}
#endif