// Source/Elistria_Calling/Private/Attributes/LevelAttributeSet.cpp
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
 // Keep this for side-effects on level up (granting points, effects, etc.)
 // Do NOT re-broadcast OnLevelChanged here to avoid duplicate notifications:
 // PostAttributeChange (and replication) should handle broadcasting.
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
  CurrentXP       = FMath::Max(0.0f, CurrentXP);

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

  // write back final XP (no direct broadcast here; PostAttributeChange will)
  const float NewXP = FMath::Max(0.0f, CurrentXP);
  SetXP(NewXP);

  // if we leveled, update Level and XPToNextLevel (PostAttributeChange will broadcast)
  if (bLeveled)
  {
   SetLevel(static_cast<float>(CurrentLevelInt));
   SetXPToNextLevel(Needed);
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
  }

  SetXPToNextLevel(MaxXPForLevel);
 }
}

void ULevelAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
 Super::PostAttributeChange(Attribute, OldValue, NewValue);

 if (Attribute == GetXPAttribute())
 {
  OnXPChanged.Broadcast(this, OldValue, NewValue);
 }
 else if (Attribute == GetLevelAttribute())
 {
  OnLevelChanged.Broadcast(this, OldValue, NewValue);
 }
 else if (Attribute == GetXPToNextLevelAttribute())
 {
  OnXPToNextLevelChanged.Broadcast(this, OldValue, NewValue);
 }
}
