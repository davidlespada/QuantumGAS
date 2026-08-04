// Copyright Quantum. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "QuantumInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FQuantumInputAction
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "InputTag")
	FGameplayTag InputTag;
};

UCLASS()
class QUANTUMGAS_API UQuantumInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& Tag) const;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& Tag) const;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputAction"))
	TArray<FQuantumInputAction> NativeInputActions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputAction"))
	TArray<FQuantumInputAction> AbilityInputActions;
};
