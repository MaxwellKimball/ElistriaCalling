// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "PlayerGameplayAbilitiesDataAsset.h"
#include "ElistriaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ELISTRIA_CALLING_API UElistriaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable)
	void ServerActivateAbilityByInputID(FGameplayAbilitySpecHandle Handle, int32 InputID);

	UFUNCTION(BlueprintCallable)
	void EquipAbility(TSubclassOf<UGameplayAbility> NewAbility, int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	void UnequipAbility(int32 SlotIndex);

	void RefreshInputBindings();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilitiesChanged, UElistriaAbilitySystemComponent*, ASC);
	UPROPERTY(BlueprintAssignable)
	FOnAbilitiesChanged OnAbilitiesChanged;

	void GrantAbilitiesFromDataAsset(const UPlayerGameplayAbilitiesDataAsset* AbilitiesDataAsset);
	virtual void AbilityLocalInputPressed(int32 InputID) override;

private:
	TMap<int32, FGameplayAbilitySpecHandle> InputIDToAbilitySpecHandleMap;

	UPROPERTY()
	TMap<int32, FGameplayAbilitySpecHandle> SlotToAbilityHandleMap;

	void ServerActivateAbilityByInputID_Implementation(FGameplayAbilitySpecHandle Handle, int32 InputID);
};
