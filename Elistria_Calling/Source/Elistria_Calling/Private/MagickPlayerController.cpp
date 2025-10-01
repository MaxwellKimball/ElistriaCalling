// Fill out your copyright notice in the Description page of Project Settings.


#include "MagickPlayerController.h"

#include "MagickPlayerState.h"

void AMagickPlayerController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Display, TEXT("OnPossess"));
	AMagickPlayerState* PS = GetPlayerState<AMagickPlayerState>();
	if (PS)
	{
		PS->SetupAbilityActorInfo();
	}
}
