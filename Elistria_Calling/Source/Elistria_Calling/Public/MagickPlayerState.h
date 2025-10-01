// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ElistriaAbilitySystemComponent.h"
#include "ManaAttributeSet.h"
#include "MagickPlayerController.h"
#include "MagickPlayerState.generated.h"

UCLASS(Config=game)
class ELISTRIA_CALLING_API AMagickPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	

	virtual void BeginPlay() override;

public:
	AMagickPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UElistriaAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SetupAbilityActorInfo();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Abilities, Replicated)
	TObjectPtr<class UElistriaAbilitySystemComponent> ElistriaAbilitySystemComponent;

	UPROPERTY(Replicated)
	TObjectPtr<class UManaAttributeSet> ManaSet;
};
