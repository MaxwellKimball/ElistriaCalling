// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerGameplayAbilitiesDataAsset.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

class UPlayerGameplayAbilitiesDataAsset;
class UInputMappingContext;
class UElistriaEnhancedInputComponent;
class UElistriaAbilitySystemComponent;
class AMagickPlayerState;
struct FInputActionInstance;

#include "MagickPlayerController.generated.h"

/**
 * 
 */



UCLASS()
class ELISTRIA_CALLING_API AMagickPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Input")
	void RebindAbilityInputs();

	UFUNCTION()
	void OnASCGranted(UElistriaAbilitySystemComponent* ASC);

	UFUNCTION()
	void HandleInput(const FInputActionInstance& Instance, FGameplayTag InputTag);
	
	UFUNCTION()
	void OnAbilitiesChanged(UElistriaAbilitySystemComponent* ASC);

	UFUNCTION()
	void AbilityInputTag(const FInputActionInstance& Instance, FGameplayTag InputTag);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UPlayerGameplayAbilitiesDataAsset> InputAbilitiesDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
};
