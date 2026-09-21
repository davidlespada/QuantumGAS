// Copyright (c) 2026 David L. Espada. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/QuantumPlayerCharacter.h"
#include "QuantumPlayerCharacter_FirstPerson.generated.h"

/**
 * First-person player character with a visible first-person mesh.
 * This preserves the previous AQuantumPlayerCharacter behavior:
 * camera attached to the first-person mesh head socket.
 */
UCLASS(meta = (PrioritizeCategories = "Ability&Input"))
class QUANTUMGAS_API AQuantumPlayerCharacter_FirstPerson : public AQuantumPlayerCharacter
{
	GENERATED_BODY()

public:
	AQuantumPlayerCharacter_FirstPerson();

protected:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> FirstPersonMeshComponent;
};
