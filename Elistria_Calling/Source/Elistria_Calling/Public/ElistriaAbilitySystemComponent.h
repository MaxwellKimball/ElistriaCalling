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
class UPlayerGameplayAbilitiesDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnASCGrantedInputAbilties, UElistriaAbilitySystemComponent*, ASC);

UCLASS()
class ELISTRIA_CALLING_API UElistriaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="AbilitySystem")
	FOnASCGrantedInputAbilties OnGrantedInputAbilties;

	UFUNCTION(BlueprintCallable, Category="AbilitySystem")
	void GrantAbilitiesFromDataAsset(const UPlayerGameplayAbilitiesDataAsset* AbilitiesDataAsset);

	UFUNCTION(BlueprintCallable, Category="AbilitySystem")
	void HandleInputTag(ETriggerEvent EventType, FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable, Category="AbilitySystem")
	void ConfirmTargetingInput(){TargetConfirm();}

	UFUNCTION(BlueprintCallable, Category="AbilitySystem")
	void CancelTargetingInput(){TargetCancel();}

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilitiesChanged, UElistriaAbilitySystemComponent*, ASC);
	UPROPERTY(BlueprintAssignable)
	FOnAbilitiesChanged OnAbilitiesChanged;

private:
	UPROPERTY()
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> TagToSpecHandleMap;
};
