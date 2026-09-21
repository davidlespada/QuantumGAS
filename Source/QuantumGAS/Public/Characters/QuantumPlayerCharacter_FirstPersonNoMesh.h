// Copyright (c) 2026 David L. Espada. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/QuantumPlayerCharacter.h"
#include "QuantumPlayerCharacter_FirstPersonNoMesh.generated.h"

/**
 * First-person player character without a visible mesh.
 * Camera is attached to the capsule at eye height; the inherited
 * third-person mesh is hidden (left empty, as it cannot be removed).
 */
UCLASS(meta = (PrioritizeCategories = "Ability&Input"))
class QUANTUMGAS_API AQuantumPlayerCharacter_FirstPersonNoMesh : public AQuantumPlayerCharacter
{
	GENERATED_BODY()

public:
	AQuantumPlayerCharacter_FirstPersonNoMesh();
};
