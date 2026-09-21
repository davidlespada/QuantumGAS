// Copyright (c) 2026 David L. Espada. All Rights Reserved.


#include "Game/QuantumPlayerController.h"

#include "AbilitySystemComponent.h"
#include "Characters/QuantumCharacter.h"
#include "Game/QuantumPlayerState.h"
#include "GAS/QuantumASC.h"

void AQuantumPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);

	// The ASC lives on the PlayerState (Mixed replication mode), so OwnerActor must be
	// the PlayerState and AvatarActor the pawn. If PlayerState hasn't replicated yet,
	// skip here — the character's OnRep_PlayerState will init once it arrives.
	AQuantumPlayerState* PS = GetPlayerState<AQuantumPlayerState>();
	AQuantumCharacter* QuantumCharacter = Cast<AQuantumCharacter>(P);
	if (IsValid(PS) && IsValid(QuantumCharacter))
	{
		if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
		{
			ASC->InitAbilityActorInfo(PS, QuantumCharacter);
		}
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
	// PlayerState can be null (e.g. before replication/possession, during login/travel,
	// or for a second player joining a listen server). The caller expects a nullable
	// result, so use soft casts and return nullptr instead of checking/crashing.
	const AQuantumPlayerState* PS = GetPlayerState<AQuantumPlayerState>();
	if (!IsValid(PS))
	{
		return nullptr;
	}
	return Cast<UQuantumASC>(PS->GetAbilitySystemComponent());
}
