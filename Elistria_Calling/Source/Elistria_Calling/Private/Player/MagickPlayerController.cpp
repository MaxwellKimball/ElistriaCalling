// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MagickPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PlayerGameplayAbilitiesDataAsset.h"
#include "ElistriaEnhancedInputComponent.h"
#include "ElistriaAbilitySystemComponent.h"
#include "Player/MagickPlayerState.h"

void AMagickPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (InputMappingContext)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Sub->AddMappingContext(InputMappingContext,0);
		}
	}
}

void AMagickPlayerController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	if (AMagickPlayerState* PS = GetPlayerState<AMagickPlayerState>())
	{
		if (UElistriaAbilitySystemComponent* ASC  = PS->GetAbilitySystemComponent())
		{
			PS->SetupAbilityActorInfo();
			ASC->OnAbilitiesChanged.AddDynamic(this, &AMagickPlayerController::OnASCGranted);
			if (InputAbilitiesDataAsset)
			{
				ASC->GrantAbilitiesFromDataAsset(InputAbilitiesDataAsset);
			}
		}
	}
}

void AMagickPlayerController::OnAbilitiesChanged(UElistriaAbilitySystemComponent* ASC)
{
	RebindAbilityInputs();
}

void AMagickPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	RebindAbilityInputs();
}

void AMagickPlayerController::OnASCGranted(UElistriaAbilitySystemComponent* ASC)
{
	RebindAbilityInputs();
}


void AMagickPlayerController::RebindAbilityInputs()
{
	if (UElistriaEnhancedInputComponent* EIC = Cast<UElistriaEnhancedInputComponent>(InputComponent))
	{
		EIC->ClearAbilityBindings();
		if (InputAbilitiesDataAsset)
		{
			EIC->BindAbilityActionsByTag(InputAbilitiesDataAsset,this,&AMagickPlayerController::HandleInput);
		}
	}
}

void AMagickPlayerController::AbilityInputTag(const FInputActionInstance& Instance, FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	if (AMagickPlayerState* PS = GetPlayerState<AMagickPlayerState>())
	{
		if (UElistriaAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
		{
			ASC->HandleInputTag(Instance.GetTriggerEvent(), InputTag);
		}
	}
}

void AMagickPlayerController::HandleInput(const FInputActionInstance& Instance, FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	if (AMagickPlayerState* PS = GetPlayerState<AMagickPlayerState>())
	{
		if (UElistriaAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
		{
			ASC->HandleInputTag(Instance.GetTriggerEvent(), InputTag);
		}
	}
}
