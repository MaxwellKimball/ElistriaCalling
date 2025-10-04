// Fill out your copyright notice in the Description page of Project Settings.


#include "ElistriaAbilitySystemComponent.h"

#include "PlayerGameplayAbilitiesDataAsset.h"

void UElistriaAbilitySystemComponent::ServerActivateAbilityByInputID_Implementation(FGameplayAbilitySpecHandle Handle,int32 InputID)
{
	TryActivateAbility(Handle);
}

void UElistriaAbilitySystemComponent::GrantAbilitiesFromDataAsset(const UPlayerGameplayAbilitiesDataAsset* AbilitiesDataAsset)
{
	if (!AbilitiesDataAsset) return;

	for (const FGameplayInputAbilityInfo& AbilityInfo : AbilitiesDataAsset->GetInputAbilities())
	{
		if (AbilityInfo.IsValid())
		{
			FGameplayAbilitySpec AbilitySpec(AbilityInfo.AbilityClass, 1, AbilityInfo.InputID);
			FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
			InputIDToAbilitySpecHandleMap.Add(AbilityInfo.InputID, SpecHandle);
		}
	}
}

void UElistriaAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{
	if (FGameplayAbilitySpecHandle* HandlePtr = SlotToAbilityHandleMap.Find(InputID))
	{
		if (GetOwnerRole() < ROLE_Authority)
		{
			ServerActivateAbilityByInputID(*HandlePtr, InputID);
		}
		TryActivateAbility(*HandlePtr);
	}
}

void UElistriaAbilitySystemComponent::EquipAbility(TSubclassOf<UGameplayAbility> NewAbility, int32 SlotIndex)
{
	if (!NewAbility) return;
	UnequipAbility(SlotIndex);

	FGameplayAbilitySpec Spec(NewAbility,1,SlotIndex);
	FGameplayAbilitySpecHandle SpecHandle = GiveAbility(Spec);
	SlotToAbilityHandleMap.Add(SlotIndex, SpecHandle);

	OnAbilitiesChanged.Broadcast(this);
}

void UElistriaAbilitySystemComponent::UnequipAbility(int32 SlotIndex)
{
	if (FGameplayAbilitySpecHandle* HandlePtr = SlotToAbilityHandleMap.Find(SlotIndex))
	{
		ClearAbility(*HandlePtr);
		SlotToAbilityHandleMap.Remove(SlotIndex);
		
		OnAbilitiesChanged.Broadcast(this);
	}
}
