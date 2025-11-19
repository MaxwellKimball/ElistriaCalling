// c++
#include "Attributes/LevelAttributeSet.h"

ULevelAttributeSet::ULevelAttributeSet()
{
	InitLevel(1.0f);
	InitXP(0.0f);
	InitMaxLevel(100.0f);
	InitXPToNextLevel(ComputeXPForLevel(1));
}

void ULevelAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULevelAttributeSet, Level,        COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULevelAttributeSet, XP,           COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULevelAttributeSet, XPToNextLevel,COND_None, REPNOTIFY_Always);
}

float ULevelAttributeSet::ComputeXPForLevel(int32 InLevel) const
{
	const int32 SafeLevel = FMath::Max(1, InLevel);
	return 100.f + 50.f * FMath::Max(0, SafeLevel - 1);
}

void ULevelAttributeSet::OnRep_Level(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULevelAttributeSet, Level, OldValue);
	OnLevelChanged.Broadcast(this, OldValue.GetCurrentValue(), Level.GetCurrentValue());
}

void ULevelAttributeSet::OnRep_XP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULevelAttributeSet, XP, OldValue);
	OnXPChanged.Broadcast(this, OldValue.GetCurrentValue(), XP.GetCurrentValue());
}

void ULevelAttributeSet::OnRep_XPToNextLevel(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULevelAttributeSet, XPToNextLevel, OldValue);
	OnXPToNextLevelChanged.Broadcast(this, OldValue.GetCurrentValue(), XPToNextLevel.GetCurrentValue());
}

void ULevelAttributeSet::HandleLevelUp(int32 LevelsGained)
{
	const float NewLevel = GetLevel();
	const float OldLevel = NewLevel - LevelsGained;
	OnLevelChanged.Broadcast(this, OldLevel, NewLevel);
}

void ULevelAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute& Attr = Data.EvaluatedData.Attribute;

	// XP modified directly by GameplayEffect
	if (Attr == GetXPAttribute())
	{
		// clamp XP non-negative
		float CurrentXP = GetXP();
		float OldXP     = CurrentXP;
		CurrentXP       = FMath::Max(0.0f, CurrentXP);

		if (!FMath::IsNearlyEqual(OldXP, CurrentXP))
		{
			SetXP(CurrentXP);
			OnXPChanged.Broadcast(this, OldXP, CurrentXP);
		}

		// process level ups
		const int32 MaxLvl = FMath::FloorToInt(GetMaxLevel());
		int32 CurrentLevelInt = FMath::Clamp(FMath::FloorToInt(GetLevel()), 1, MaxLvl);
		float Needed = GetXPToNextLevel();

		bool  bLeveled     = false;
		int32 LevelsGained = 0;

		while (CurrentXP >= Needed && CurrentLevelInt < MaxLvl)
		{
			CurrentXP      -= Needed;
			++CurrentLevelInt;
			Needed          = ComputeXPForLevel(CurrentLevelInt);
			bLeveled        = true;
			++LevelsGained;
		}

		// write back final XP
		OldXP        = GetXP();
		const float NewXP = FMath::Max(0.0f, CurrentXP);
		if (!FMath::IsNearlyEqual(OldXP, NewXP))
		{
			SetXP(NewXP);
			OnXPChanged.Broadcast(this, OldXP, NewXP);
		}

		// if we leveled, update Level and XPToNextLevel
		if (bLeveled)
		{
			SetLevel(static_cast<float>(CurrentLevelInt));
			SetXPToNextLevel(Needed);
			OnXPToNextLevelChanged.Broadcast(this, XPToNextLevel.GetCurrentValue(), XPToNextLevel.GetCurrentValue());
			HandleLevelUp(LevelsGained);
		}
	}

	// if some GE directly sets Level, clamp and fix XP/XPToNextLevel
	if (Attr == GetLevelAttribute())
	{
		const int32 RawLevel = FMath::FloorToInt(GetLevel());
		const int32 Clamped  = FMath::Clamp(RawLevel, 1, FMath::FloorToInt(GetMaxLevel()));

		if (Clamped != RawLevel)
		{
			SetLevel(static_cast<float>(Clamped));
		}

		const float MaxXPForLevel = ComputeXPForLevel(Clamped);

		const float OldXP = GetXP();
		const float NewXP = FMath::Clamp(OldXP, 0.0f, MaxXPForLevel);
		if (!FMath::IsNearlyEqual(OldXP, NewXP))
		{
			SetXP(NewXP);
			OnXPChanged.Broadcast(this, OldXP, NewXP);
		}

		SetXPToNextLevel(MaxXPForLevel);
		OnXPToNextLevelChanged.Broadcast(this, XPToNextLevel.GetCurrentValue(), XPToNextLevel.GetCurrentValue());
	}
}
