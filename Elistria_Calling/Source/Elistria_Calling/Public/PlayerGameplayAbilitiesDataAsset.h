// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "PlayerGameplayAbilitiesDataAsset.generated.h"

/**
 * 
 */
class UInputAction;

USTRUCT()
struct FGameplayInputAbilityInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(VisibleAnywhere, Category = "GameplayInputAbilityInfo")
	int32 InputID;

	bool IsValid() const
	{
		return AbilityClass && InputAction;
	}

	bool operator==(const FGameplayInputAbilityInfo& other) const
	{
		return AbilityClass == other.AbilityClass && InputID == other.InputID;
	}

	bool operator!=(const FGameplayInputAbilityInfo& other) const
	{
		return !operator==(other);
	}

	friend uint32 GetTypeHash(const FGameplayInputAbilityInfo& Item)
	{
		return HashCombine(GetTypeHash(Item.AbilityClass), Item.InputID);
	}

	FGameplayInputAbilityInfo()
	: InputID(INDEX_NONE)
	{
	}
};

UCLASS()
class ELISTRIA_CALLING_API UPlayerGameplayAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TSet<FGameplayInputAbilityInfo> InputAbilities;

public:
	UPlayerGameplayAbilitiesDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	const TSet<FGameplayInputAbilityInfo>& GetInputAbilities() const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
