// Copyright Quantum. All rights reserved


#include "Game/QuantumPlayerController.h"

#include "AbilitySystemComponent.h"
#include "Characters/QuantumCharacter.h"
#include "Game/QuantumPlayerState.h"
#include "GAS/QuantumASC.h"

void AQuantumPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
	
	AQuantumCharacter* QuantumCharacter = Cast<AQuantumCharacter>(P);
	if (IsValid(QuantumCharacter))
	{
		QuantumCharacter->GetAbilitySystemComponent()->InitAbilityActorInfo(QuantumCharacter, QuantumCharacter);
	}
}

void AQuantumPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UQuantumASC* ASC = GetQuantumASC())
	{
		ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

UQuantumASC* AQuantumPlayerController::GetQuantumASC() const
{
	const AQuantumPlayerState* PS = CastChecked<AQuantumPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
	return CastChecked<UQuantumASC>(PS->GetAbilitySystemComponent());
}
