// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/QuantumInputConfig.h"

const UInputAction* UQuantumInputConfig::FindNativeInputActionForTag(const FGameplayTag& Tag) const
{
	for (const FQuantumInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && Action.InputTag == Tag)
		{
			return Action.InputAction;
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *Tag.ToString(), *GetNameSafe(this));
	return nullptr;
}

const UInputAction* UQuantumInputConfig::FindAbilityInputActionForTag(const FGameplayTag& Tag) const
{
	for (const FQuantumInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == Tag)
		{
			return Action.InputAction;
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *Tag.ToString(), *GetNameSafe(this));
	return nullptr;
}
