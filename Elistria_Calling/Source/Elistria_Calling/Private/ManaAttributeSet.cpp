// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaAttributeSet.h"

UManaAttributeSet::UManaAttributeSet()
{
	InitMana(100.0f);
	InitMaxMana(100.0f);
}

void UManaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UManaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UManaAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, Mana, OldValue);
	const float OldMana = OldValue.GetCurrentValue();
	const float NewMana = GetMana();
	OnManaChanged.Broadcast(this, OldMana, NewMana);
}

void UManaAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UManaAttributeSet, MaxMana, OldValue);
	const float OldMaxMana = OldValue.GetCurrentValue();
	const float NewMaxMana = GetMaxMana();
	OnMaxManaChanged.Broadcast(this, OldMaxMana, NewMaxMana);
}