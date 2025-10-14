// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElistriaAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "ManaAttributeSet.h"
#include "LevelAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ELISTRIA_CALLING_API ULevelAttributeSet : public UElistriaAttributeSetBase
{
	GENERATED_BODY()

public:
	ULevelAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_Level)
	FGameplayAttributeData Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_XP)
	FGameplayAttributeData XP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_XPToNextLevel)
	FGameplayAttributeData XPToNextLevel;

	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData XPGain;

	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData XPLoss;

	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData MaxLevel;

	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, XP)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, Level)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, MaxLevel)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, XPToNextLevel)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, XPGain)
	ATTRIBUTE_ACCESSORS(ULevelAttributeSet, XPLoss)

	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_XP(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_XPToNextLevel(const FGameplayAttributeData& OldValue);

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnLevelChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnXPChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnXPToNextLevelChanged;
	
protected:
	float ComputeXPForLevel(int32 InLevel) const;
	void HandleLevelUp(int32 LevelsGained);
	void ConsumeXPGain();
	void TryProcessLevelUp();
};
