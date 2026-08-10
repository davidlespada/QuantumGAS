// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "QuantumGameplayAbilityBase.generated.h"

UENUM(BlueprintType)
enum class EQuantumAbilityActivationPolicy : uint8
{
	OnInputTriggered,
	WhileInputActive
};

UCLASS()
class QUANTUMGAS_API UQuantumGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	EQuantumAbilityActivationPolicy GetActivationPolicy() const {return ActivationPolicy;};
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability Activation")
	EQuantumAbilityActivationPolicy ActivationPolicy;
};
