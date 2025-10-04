// Fill out your copyright notice in the Description page of Project Settings.


#include "MagickPlayerController.h"

#include "ElistriaEnhancedInputComponent.h"
#include "MagickPlayerState.h"

void AMagickPlayerController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Display, TEXT("OnPossess"));
	AMagickPlayerState* PS = GetPlayerState<AMagickPlayerState>();
	UElistriaAbilitySystemComponent* ASC = PS ? PS->GetAbilitySystemComponent() : nullptr;
	if (PS)
	{
		PS->SetupAbilityActorInfo();
		if (ASC)
		{
			ASC->OnAbilitiesChanged.AddDynamic(this,&AMagickPlayerController::OnAbilitiesChanged);
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
	if (UElistriaEnhancedInputComponent* EIC = Cast<UElistriaEnhancedInputComponent>(InputComponent))
	{
		if (InputAbilitiesDataAsset)
		{
			EIC->BindAbilityActions(InputAbilitiesDataAsset, this, &AMagickPlayerController::AbilityInputPressed);
		}
	}
}

void AMagickPlayerController::AbilityInputPressed(int32 InputID)
{
	if (AMagickPlayerState* PS = GetPlayerState<AMagickPlayerState>())
	{
		if (UElistriaAbilitySystemComponent* ASC = PS ? PS->GetAbilitySystemComponent() : nullptr)
		{
			ASC->AbilityLocalInputPressed(InputID);
		}
	}
}

void AMagickPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UInputMappingContext* IMC = InputMappingContext)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

void AMagickPlayerController::RebindAbilityInputs()
{
	if (UElistriaEnhancedInputComponent* EIC = Cast<UElistriaEnhancedInputComponent>(InputComponent))
	{
		EIC -> ClearAbilityBindings();
		if (InputAbilitiesDataAsset)
		{
			EIC->BindAbilityActions(InputAbilitiesDataAsset,this,&AMagickPlayerController::AbilityInputPressed);
		}
	}
}
