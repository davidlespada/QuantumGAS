// Copyright (c) 2026 David L. Espada. All Rights Reserved.


#include "Characters/QuantumPlayerCharacter_FirstPerson.h"

#include "Camera/CameraComponent.h"

AQuantumPlayerCharacter_FirstPerson::AQuantumPlayerCharacter_FirstPerson()
{
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMeshComponent"));
	FirstPersonMeshComponent->SetupAttachment(GetMesh());
	FirstPersonMeshComponent->SetOnlyOwnerSee(true);
	FirstPersonMeshComponent->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;

	CameraComponent->SetupAttachment(FirstPersonMeshComponent, TEXT("head"));
	CameraComponent->SetFieldOfView(80.0f);
}
