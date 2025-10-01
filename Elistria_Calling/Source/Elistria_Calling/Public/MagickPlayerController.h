// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MagickPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ELISTRIA_CALLING_API AMagickPlayerController : public APlayerController
{
	GENERATED_BODY()


	virtual void OnPossess(APawn* InPawn) override;
};
