// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerGameplayAbilitiesDataAsset.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "ElistriaEnhancedInputComponent.h"
#include "MagickPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ELISTRIA_CALLING_API AMagickPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnAbilitiesChanged(UElistriaAbilitySystemComponent* ASC);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UPlayerGameplayAbilitiesDataAsset> InputAbilitiesDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void AbilityInputPressed(int32 InputID);

	virtual void BeginPlay() override;

	void RebindAbilityInputs();
};
