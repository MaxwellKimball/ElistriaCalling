// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/LevelAttributeSet.h"

ULevelAttributeSet::ULevelAttributeSet()
{
	InitLevel(1.0f);
	InitXP(0.0f);
	InitXPToNextLevel(ComputeXPForLevel(1));
}

void ULevelAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ULevelAttributeSet, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULevelAttributeSet, XP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULevelAttributeSet, XPToNextLevel, COND_None, REPNOTIFY_Always);
}

float ULevelAttributeSet::ComputeXPForLevel(int32 InLevel) const
{
	return 100.f + 50.f * FMath::Max(0, InLevel - 1);
}


void ULevelAttributeSet::OnRep_Level(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULevelAttributeSet, Level, OldValue);
	UE_LOG(LogTemp, Log, TEXT("Level changed from %f to %f"), OldValue.GetCurrentValue(), Level.GetCurrentValue());
	OnLevelChanged.Broadcast(this, OldValue.GetCurrentValue(), Level.GetCurrentValue());
}

void ULevelAttributeSet::OnRep_XP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULevelAttributeSet, XP, OldValue);
	UE_LOG( LogTemp, Log, TEXT("XP changed from %f to %f"), OldValue.GetCurrentValue(), XP.GetCurrentValue());
	OnXPChanged.Broadcast(this, OldValue.GetCurrentValue(), XP.GetCurrentValue());
}

void ULevelAttributeSet::OnRep_XPToNextLevel(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULevelAttributeSet, XPToNextLevel, OldValue);
	OnXPToNextLevelChanged.Broadcast(this, OldValue.GetCurrentValue(), XPToNextLevel.GetCurrentValue());
}
void ULevelAttributeSet::ConsumeXPGain()
{
	const float Gain = GetXPGain();
	if (Gain > 0.0f)
	{
		float OldXP = GetXP();
		float NewXP =OldXP + Gain;
		SetXP(NewXP);
		SetXPGain(0.0f);
		OnXPChanged.Broadcast(this, GetXP(), Gain);
		OnLevelChanged.Broadcast(this, GetXP()-Gain, Level.GetCurrentValue());
	}
}

void ULevelAttributeSet::TryProcessLevelUp()
{
	bool Leveled = false;
	int32 LevelsGained = 0;
	float CurrentXP = GetXP();
	float Needed = GetXPToNextLevel();
	int32 CurrentLevelInt = FMath::FloorToInt(GetLevel());

	while (CurrentXP>= Needed)
	{
		CurrentXP -= Needed;
		CurrentLevelInt+=1;
		Needed = ComputeXPForLevel(CurrentLevelInt);
		Leveled = true;
	}
	if (Leveled)
	{
		SetLevel(static_cast<float>(CurrentLevelInt));
		SetXPToNextLevel(Needed);
	}
	SetXP(FMath::Max(0.0f, CurrentXP));
	if (Leveled)
	{
		HandleLevelUp(LevelsGained);
	}
}

void ULevelAttributeSet::HandleLevelUp(int32 LevelsGained)
{
	// This function can be expanded to include additional logic when a level-up occurs.
	// For example, you might want to notify other systems, play a sound, etc.

	OnLevelChanged.Broadcast(this, GetLevel() - LevelsGained, GetLevel());
}

void ULevelAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetXPAttribute())
	{
		ConsumeXPGain();
	}
	
	if (Data.EvaluatedData.Attribute == GetXPGainAttribute()||Data.EvaluatedData.Attribute == GetXPAttribute())
	{
		SetXP(FMath::Max(0.0f, GetXP()));
		TryProcessLevelUp();
	}

	if (Data.EvaluatedData.Attribute == GetLevelAttribute())
	{
		const int32 Lvl = FMath::Max(1,FMath::FloorToInt(GetLevel()));
		SetLevel(static_cast<float>(Lvl));
		SetXP(FMath::Clamp(GetXP(),0.0f,ComputeXPForLevel(Lvl)));
		SetXPToNextLevel(ComputeXPForLevel(Lvl));
		OnXPToNextLevelChanged.Broadcast(this, XPToNextLevel.GetCurrentValue(), XPToNextLevel.GetCurrentValue());
	}
}
