// Copyright (c) 2026 David L. Espada. All Rights Reserved.


#include "Characters/QuantumPlayerCharacter_ThirdPerson.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AQuantumPlayerCharacter_ThirdPerson::AQuantumPlayerCharacter_ThirdPerson()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->SocketOffset = FVector(0.0f, 50.0f, 50.0f);
	SpringArmComponent->TargetOffset = FVector(0.0f, 0.0f, 50.0f);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 10.0f;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraRotationLagSpeed = 10.0f;
	SpringArmComponent->bDoCollisionTest = true;
	SpringArmComponent->ProbeSize = 12.0f;

	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Standard third-person rotation behavior.
	bUseControllerRotationYaw = false;

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;
	}
}
