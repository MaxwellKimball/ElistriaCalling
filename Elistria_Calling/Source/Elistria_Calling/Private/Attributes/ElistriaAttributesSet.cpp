// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/ElistriaAttributesSet.h"

#include "GameplayEffectExtension.h"

UElistriaAttributesSet::UElistriaAttributesSet()
{
	InitArchery(1);
	InitAthletics(1);
	InitDeceit(1);
	InitDefensibility(1);
	InitDiscernment(1);
	InitLightWeaponry(1);
	InitHeavyWeaponry(1);
	InitPerception(1);
	InitStealth(1);
	InitSurvival(1);
	InitAttributePoints(0);
}

void UElistriaAttributesSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Archery, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Athletics, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Deceit, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Defensibility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Discernment, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, LightWeaponry, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, HeavyWeaponry, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Perception, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Stealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, Survival, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UElistriaAttributesSet, AttributePoints, COND_None, REPNOTIFY_Always);
}

void UElistriaAttributesSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Helper lambda to handle clamping and broadcasting for primary attributes (1..100)
	auto HandleStat = [this, &Data](const FGameplayAttribute& Attr, float(UElistriaAttributesSet::*GetFunc)() const, void(UElistriaAttributesSet::*SetFunc)(float), FAttributeChangedEvent& Event)
	{
		if (Data.EvaluatedData.Attribute == Attr)
		{
			const float Old = (this->*GetFunc)();
			const float New = FMath::Clamp(Old, 1.0f, 100.0f);
			if (!FMath::IsNearlyEqual(Old, New))
			{
				(this->*SetFunc)(New);
			}
			Event.Broadcast(this, Old, New);
		}
	};

	// Archery
	if (Data.EvaluatedData.Attribute == GetArcheryAttribute())
	{
		const float Old = GetArchery();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetArchery(New);
		OnArcheryChanged.Broadcast(this, Old, New);
	}

	// Athletics
	if (Data.EvaluatedData.Attribute == GetAthleticsAttribute())
	{
		const float Old = GetAthletics();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetAthletics(New);
		OnAthleticsChanged.Broadcast(this, Old, New);
	}

	// Deceit
	if (Data.EvaluatedData.Attribute == GetDeceitAttribute())
	{
		const float Old = GetDeceit();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetDeceit(New);
		OnDeceitChanged.Broadcast(this, Old, New);
	}

	// Defensibility
	if (Data.EvaluatedData.Attribute == GetDefensibilityAttribute())
	{
		const float Old = GetDefensibility();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetDefensibility(New);
		OnDefensibilityChanged.Broadcast(this, Old, New);
	}

	// Discernment
	if (Data.EvaluatedData.Attribute == GetDiscernmentAttribute())
	{
		const float Old = GetDiscernment();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetDiscernment(New);
		OnDiscernmentChanged.Broadcast(this, Old, New);
	}

	// LightWeaponry
	if (Data.EvaluatedData.Attribute == GetLightWeaponryAttribute())
	{
		const float Old = GetLightWeaponry();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetLightWeaponry(New);
		OnLightWeaponryChanged.Broadcast(this, Old, New);
	}

	// HeavyWeaponry
	if (Data.EvaluatedData.Attribute == GetHeavyWeaponryAttribute())
	{
		const float Old = GetHeavyWeaponry();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetHeavyWeaponry(New);
		OnHeavyWeaponryChanged.Broadcast(this, Old, New);
	}

	// Perception
	if (Data.EvaluatedData.Attribute == GetPerceptionAttribute())
	{
		const float Old = GetPerception();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetPerception(New);
		OnPerceptionChanged.Broadcast(this, Old, New);
	}

	// Stealth
	if (Data.EvaluatedData.Attribute == GetStealthAttribute())
	{
		const float Old = GetStealth();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetStealth(New);
		OnStealthChanged.Broadcast(this, Old, New);
	}

	// Survival
	if (Data.EvaluatedData.Attribute == GetSurvivalAttribute())
	{
		const float Old = GetSurvival();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetSurvival(New);
		OnSurvivalChanged.Broadcast(this, Old, New);
	}

	// Thievery
	if (Data.EvaluatedData.Attribute == GetThieveryAttribute())
	{
		const float Old = GetThievery();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetThievery(New);
		OnThieveryChanged.Broadcast(this, Old, New);
	}

	// Will
	if (Data.EvaluatedData.Attribute == GetWillAttribute())
	{
		const float Old = GetWill();
		const float New = FMath::Clamp(Old, 1.0f, 100.0f);
		if (!FMath::IsNearlyEqual(Old, New)) SetWill(New);
		OnWillChanged.Broadcast(this, Old, New);
	}

	// AttributePoints (ensure non-negative)
	if (Data.EvaluatedData.Attribute == GetAttributePointsAttribute())
	{
		const float Old = GetAttributePoints();
		const float New = FMath::Max(0.0f, Old);
		if (!FMath::IsNearlyEqual(Old, New)) SetAttributePoints(New);
		OnAttributePointsChanged.Broadcast(this, Old, New);
	}
}
void UElistriaAttributesSet::OnRep_Archery(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Archery, OldValue);
	OnArcheryChanged.Broadcast(this, OldValue.GetCurrentValue(), Archery.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Athletics(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Athletics, OldValue);
	OnAthleticsChanged.Broadcast(this, OldValue.GetCurrentValue(), Athletics.GetCurrentValue());
	
}

void UElistriaAttributesSet::OnRep_Deceit(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Deceit, OldValue);
	OnDeceitChanged.Broadcast(this, OldValue.GetCurrentValue(), Deceit.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Defensibility(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Defensibility, OldValue);
	OnDefensibilityChanged.Broadcast(this, OldValue.GetCurrentValue(), Defensibility.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Discernment(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Discernment, OldValue);
	OnDiscernmentChanged.Broadcast(this, OldValue.GetCurrentValue(), Discernment.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_LightWeaponry(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, LightWeaponry, OldValue);
	OnLightWeaponryChanged.Broadcast(this, OldValue.GetCurrentValue(), LightWeaponry.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_HeavyWeaponry(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, HeavyWeaponry, OldValue);
	OnHeavyWeaponryChanged.Broadcast(this, OldValue.GetCurrentValue(), HeavyWeaponry.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Perception(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Perception, OldValue);
	OnPerceptionChanged.Broadcast(this, OldValue.GetCurrentValue(), Perception.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Stealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Stealth, OldValue);
	OnStealthChanged.Broadcast(this, OldValue.GetCurrentValue(), Stealth.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Survival(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Survival, OldValue);
	OnSurvivalChanged.Broadcast(this, OldValue.GetCurrentValue(), Survival.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_AttributePoints(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, AttributePoints, OldValue);
	OnAttributePointsChanged.Broadcast(this, OldValue.GetCurrentValue(), AttributePoints.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Thievery(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Thievery, OldValue);
	OnThieveryChanged.Broadcast(this, OldValue.GetCurrentValue(), Thievery.GetCurrentValue());
}

void UElistriaAttributesSet::OnRep_Will(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UElistriaAttributesSet, Will, OldValue);
	OnWillChanged.Broadcast(this, OldValue.GetCurrentValue(), Will.GetCurrentValue());
}
