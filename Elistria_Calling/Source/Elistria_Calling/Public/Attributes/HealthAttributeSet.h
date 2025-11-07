// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ElistriaAttributeSetBase.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "HealthAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class ELISTRIA_CALLING_API UHealthAttributeSet : public UElistriaAttributeSetBase
{
	GENERATED_BODY()

public:
	UHealthAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Damage;

	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Heal;

	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Damage)
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Heal)

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnMaxHealthChanged;
};
