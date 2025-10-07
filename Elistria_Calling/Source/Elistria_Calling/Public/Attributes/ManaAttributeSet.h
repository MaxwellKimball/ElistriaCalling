// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ElistriaAttributeSetBase.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "ManaAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class ELISTRIA_CALLING_API UManaAttributeSet : public UElistriaAttributeSetBase
{
	GENERATED_BODY()

public:
	UManaAttributeSet();
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, meta = (HideFromModifiers))
	FGameplayAttributeData Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;

	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Cost;

	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Restore;
	
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, MaxMana)
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, Cost)
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, Restore)

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnMaxManaChanged;
};
