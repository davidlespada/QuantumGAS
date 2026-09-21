// Copyright (c) 2026 David L. Espada. All Rights Reserved.


#include "Characters/QuantumPlayerCharacter_FirstPersonNoMesh.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AQuantumPlayerCharacter_FirstPersonNoMesh::AQuantumPlayerCharacter_FirstPersonNoMesh()
{
	// Camera sits on the capsule at eye height; driven directly by control rotation.
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	CameraComponent->bUsePawnControlRotation = true;

	// The ACharacter mesh cannot be removed through inheritance, so hide it.
	GetMesh()->SetVisibility(false, true);
	GetMesh()->SetCastShadow(false);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::None;
}
