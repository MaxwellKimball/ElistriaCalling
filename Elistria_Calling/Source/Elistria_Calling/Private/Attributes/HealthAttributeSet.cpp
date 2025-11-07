// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/HealthAttributeSet.h"


UHealthAttributeSet::UHealthAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, Health, OldValue);
	const float OldHealth = OldValue.GetCurrentValue();
	const float NewHealth = GetHealth();
	OnHealthChanged.Broadcast(this, OldHealth, NewHealth);
}

void UHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, MaxHealth, OldValue);
	const float OldMaxHealth = OldValue.GetCurrentValue();
	const float NewMaxHealth = GetMaxHealth();
	OnMaxHealthChanged.Broadcast(this, OldMaxHealth, NewMaxHealth);
}
void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float DamageValue = GetDamage();
		const float OldHealth = GetHealth();
		const float HealthMax = GetMaxHealth();
		const float NewHealth =  FMath::Clamp(OldHealth-DamageValue,0.0f, HealthMax);
		if (OldHealth!=NewHealth)
		{
			SetHealth(NewHealth);
		}
		SetDamage(0.0f);
	}
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float HealValue = GetHeal();
		const float OldHealth = GetHealth();
		const float HealthMax = GetMaxHealth();
		const float NewHealth = FMath::Clamp(OldHealth+HealValue,0.0f, HealthMax);
		if (OldHealth!=NewHealth)
		{
			SetHealth(NewHealth);
		}
		SetHeal(0.0f);
	}
}

void UHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		const float ClampedHealth = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
		if (ClampedHealth != NewValue)
		{
			SetHealth(ClampedHealth);
		}
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		const float ClampedMaxHealth = FMath::Max(1.0f, NewValue);
		if (ClampedMaxHealth != NewValue)
		{
			SetMaxHealth(ClampedMaxHealth);
		}
	}
}