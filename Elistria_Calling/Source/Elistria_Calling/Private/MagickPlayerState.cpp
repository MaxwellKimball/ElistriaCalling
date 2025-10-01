// Fill out your copyright notice in the Description page of Project Settings.


#include "MagickPlayerState.h"




AMagickPlayerState::AMagickPlayerState()
{
	ElistriaAbilitySystemComponent = CreateDefaultSubobject<UElistriaAbilitySystemComponent>(TEXT("AbilitySystem"));
	ManaSet = CreateDefaultSubobject<UManaAttributeSet>(TEXT("ManaSet"));
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
	}
	
}
