// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MagickPlayerState.h"
#include "Player/MagickPlayerController.h"
#include "Net/UnrealNetwork.h"

AMagickPlayerState::AMagickPlayerState()
{
	ElistriaAbilitySystemComponent = CreateDefaultSubobject<UElistriaAbilitySystemComponent>(TEXT("AbilitySystem"));
	ManaSet = CreateDefaultSubobject<UManaAttributeSet>(TEXT("ManaSet"));
	HealthSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthSet"));
	StaminaSet = CreateDefaultSubobject<UStaminaAttributeSet>(TEXT("StaminaSet"));
	LevelSet = CreateDefaultSubobject<ULevelAttributeSet>(TEXT("XPSet"));
	ElistriaAttributesSet = CreateDefaultSubobject<UElistriaAttributesSet>(TEXT("ElistriaAttributesSet"));
	
}

UElistriaAbilitySystemComponent* AMagickPlayerState::GetAbilitySystemComponent() const
{
	return ElistriaAbilitySystemComponent;
}

void AMagickPlayerState::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMagickPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(AMagickPlayerState, ElistriaAbilitySystemComponent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AMagickPlayerState, ManaSet, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AMagickPlayerState, HealthSet, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AMagickPlayerState, StaminaSet, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AMagickPlayerState, LevelSet, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AMagickPlayerState, ElistriaAttributesSet, COND_None, REPNOTIFY_Always);
}

void AMagickPlayerState::SetupAbilityActorInfo()
{
	AMagickPlayerController* PC = Cast<AMagickPlayerController>(GetOwner());
	if (!PC)
	{
		return;
	}

	APawn* Pawn = PC->GetPawn();

	if (!Pawn)
	{
		return;
	}
	if (ElistriaAbilitySystemComponent)
	{
		ElistriaAbilitySystemComponent->InitAbilityActorInfo(this,Pawn);

		if (ManaSet)
		{
			ElistriaAbilitySystemComponent->AddAttributeSetSubobject(ManaSet.Get());
		}
		if (HealthSet)
		{
			ElistriaAbilitySystemComponent->AddAttributeSetSubobject(HealthSet.Get());
		}
		if (StaminaSet)
		{
			ElistriaAbilitySystemComponent->AddAttributeSetSubobject(StaminaSet.Get());
		}
		if (LevelSet)
		{
			ElistriaAbilitySystemComponent->AddAttributeSetSubobject(LevelSet.Get());
		}
		
		if (ElistriaAttributesSet)
		{
			ElistriaAbilitySystemComponent->AddAttributeSetSubobject(ElistriaAttributesSet.Get());
		}
	}
}
void AMagickPlayerState::OnRep_ElistriaAbilitySystemComponent()
{
	// Whenever the ability system component is replicated, we need to refresh the actor info
	return;
}
