// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/StaminaAttributeSet.h"

UStaminaAttributeSet::UStaminaAttributeSet()
{
	InitStamina(100.0f);
	InitMaxStamina(100.0f);
}
void UStaminaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UStaminaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStaminaAttributeSet, Stamina, OldValue);
	const float OldStamina = OldValue.GetCurrentValue();
	const float NewStamina = GetStamina();
	OnStaminaChanged.Broadcast(this, OldStamina, NewStamina);
}
void UStaminaAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStaminaAttributeSet, MaxStamina, OldValue);
	const float OldMaxStamina = OldValue.GetCurrentValue();
	const float NewMaxStamina = GetMaxStamina();
	OnMaxStaminaChanged.Broadcast(this, OldMaxStamina, NewMaxStamina);
}
void UStaminaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
	if (Data.EvaluatedData.Attribute == GetDrainAttribute())
	{
		const float DrainValue = GetDrain();
		const float OldStamina = GetStamina();
		const float StaminaMax = GetMaxStamina();
		const float NewStamina =  FMath::Clamp(OldStamina-DrainValue,0.0f, StaminaMax);
		if (OldStamina!=NewStamina)
		{
			SetStamina(NewStamina);
			OnMaxStaminaChanged.Broadcast(this, OldStamina, NewStamina);
		}
		SetDrain(0.0f);
	}
	if (Data.EvaluatedData.Attribute==GetRestoreAttribute())
	{
		const float RestoreValue = GetRestore();
		const float OldStamina = GetStamina();
		const float StaminaMax = GetMaxStamina();
		const float NewStamina = FMath::Clamp(OldStamina+RestoreValue,0.0f, StaminaMax);
		if (OldStamina!=NewStamina)
		{
			SetStamina(NewStamina);
			OnMaxStaminaChanged.Broadcast(this, OldStamina, NewStamina);
		}
	}
}