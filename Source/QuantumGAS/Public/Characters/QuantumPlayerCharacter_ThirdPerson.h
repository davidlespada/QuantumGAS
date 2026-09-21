// Copyright (c) 2026 David L. Espada. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/QuantumPlayerCharacter.h"
#include "QuantumPlayerCharacter_ThirdPerson.generated.h"

class USpringArmComponent;

/**
 * Third-person player character with a spring arm + camera fully configured in C++.
 */
UCLASS(meta = (PrioritizeCategories = "Ability&Input"))
class QUANTUMGAS_API AQuantumPlayerCharacter_ThirdPerson : public AQuantumPlayerCharacter
{
	GENERATED_BODY()

public:
	AQuantumPlayerCharacter_ThirdPerson();

protected:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
};
