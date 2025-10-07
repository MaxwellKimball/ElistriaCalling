// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/ManaAttributeSet.h"

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

void UManaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetCostAttribute())
	{
		const float CostValue = GetCost();
		const float OldMana = GetMana();
		const float ManaMax = GetMaxMana();
		const float NewMana =  FMath::Clamp(OldMana-CostValue,0.0f, ManaMax);
		if (OldMana!=NewMana)
		{
			SetMana(NewMana);
		}
		SetCost(0.0f);
	}
	if (Data.EvaluatedData.Attribute==GetRestoreAttribute())
	{
		const float RestoreValue = GetMaxMana();
		const float OldMana = GetMana();
		const float ManaMax = GetMaxMana();
		const float NewMana = FMath::Clamp(OldMana+RestoreValue,0.0f, ManaMax);
		if (OldMana!=NewMana)
		{
			SetMana(NewMana);
		}
		SetRestore(0.0f);
	}
}
