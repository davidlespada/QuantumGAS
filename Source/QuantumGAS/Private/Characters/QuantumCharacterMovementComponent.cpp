// Copyright Quantum. All rights reserved


#include "Characters/QuantumCharacterMovementComponent.h"

#include "Characters/QuantumCharacter.h"


// Sets default values for this component's properties
UQuantumCharacterMovementComponent::UQuantumCharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UQuantumCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

float UQuantumCharacterMovementComponent::GetMaxSpeed() const
{
	AQuantumCharacter* QuantumCharacter = Cast<AQuantumCharacter>(GetOwner());
	if (!IsValid(QuantumCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("QuantumCharacterMovementComponent::GetMaxSpeed() - QuantumCharacter is invalid"));
		return Super::GetMaxSpeed();
	}
	
	if (!QuantumCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("QuantumCharacterMovementComponent::GetMaxSpeed() - QuantumCharacter is null"));
		return Super::GetMaxSpeed();
	}
	
	return Super::GetMaxSpeed();
}


// Called every frame
void UQuantumCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

