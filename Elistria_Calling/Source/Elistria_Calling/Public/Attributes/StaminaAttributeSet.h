// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "ElistriaAttributeSetBase.h"
#include "HealthAttributeSet.h"
#include "StaminaAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class ELISTRIA_CALLING_API UStaminaAttributeSet : public UElistriaAttributeSetBase
{
	GENERATED_BODY()

public:
	UStaminaAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, Stamina)
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, MaxStamina)
	
	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Drain;
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, Drain)
	
	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Restore;
	ATTRIBUTE_ACCESSORS(UStaminaAttributeSet, Restore)

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnMaxStaminaChanged;
};
