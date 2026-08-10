// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/QuantumCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/QuantumASC.h"
#include "GAS/Attributes/QuantumAttributeSet.h"


void AQuantumCharacter::InitializeAttributes()
{
	if (!QuantumASC.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = QuantumASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = QuantumASC->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = QuantumASC->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), QuantumASC.Get());
	}
}

// Sets default values
AQuantumCharacter::AQuantumCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AQuantumCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (QuantumASC.IsValid())
	{
		MoveSpeedChangedDelegateHandle = QuantumASC->GetGameplayAttributeValueChangeDelegate(QuantumAttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &ThisClass::MoveSpeedChanged);
	}
}

void AQuantumCharacter::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = Data.NewValue;
}

// Called every frame
void AQuantumCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AQuantumCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AQuantumCharacter::GetAbilitySystemComponent() const
{
	return QuantumASC.Get();
}

float AQuantumCharacter::GetHealth() const
{
	if (QuantumAttributeSet.IsValid())
	{
		return QuantumAttributeSet->GetHealth();
	}
	return 0.0f;
}

bool AQuantumCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}
