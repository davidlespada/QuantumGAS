// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/QuantumASC.h"

#include "GAS/Abilities/QuantumGameplayAbilityBase.h"


// Sets default values for this component's properties
UQuantumASC::UQuantumASC()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UQuantumASC::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
			{
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UQuantumASC::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void UQuantumASC::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();
	
	// Process input held abilities
	for (const FGameplayAbilitySpecHandle& Handle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(Handle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				const UQuantumGameplayAbilityBase* QuantumAbility = CastChecked<UQuantumGameplayAbilityBase>(AbilitySpec->Ability);
				
				if (QuantumAbility->GetActivationPolicy() ==  EQuantumAbilityActivationPolicy::WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}
	
	// Process Input Pressed abilities
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;

				if (AbilitySpec->IsActive())
				{
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					const UQuantumGameplayAbilityBase* SNAbility = CastChecked<UQuantumGameplayAbilityBase>(AbilitySpec->Ability);

					if (SNAbility->GetActivationPolicy() == EQuantumAbilityActivationPolicy::OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					}
				}
			}
		}
	}
	
	// Activate target abilities
	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}
		
	// Process released abilities
	for (const FGameplayAbilitySpecHandle& ReleasedSpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(ReleasedSpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;
					
				if (AbilitySpec->IsActive())
				{
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}
	
	// Reset handles
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UQuantumASC::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UQuantumASC::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
	if (Spec.IsActive())
	{
		const UGameplayAbility* Ability = Spec.GetPrimaryInstance();
		
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		const FPredictionKey PredictionKey = Ability == nullptr
			                                     ? Spec.ActivationInfo.GetActivationPredictionKey()
			                                     : Ability->GetCurrentActivationInfo().GetActivationPredictionKey();
		
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, PredictionKey);
	}
}

void UQuantumASC::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);
	if (Spec.IsActive())
	{
		const UGameplayAbility* Ability = Spec.GetPrimaryInstance();
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		const FPredictionKey PredictionKey = Ability == nullptr
			                                     ? Spec.ActivationInfo.GetActivationPredictionKey()
			                                     : Ability->GetCurrentActivationInfo().GetActivationPredictionKey();
		
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, PredictionKey);
	}
}


