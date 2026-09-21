// Copyright (c) 2026 David L. Espada. All Rights Reserved.


#include "Characters/QuantumCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/QuantumASC.h"
#include "GAS/Attributes/QuantumAttributeSet.h"


void AQuantumCharacter::InitializeAttributes()
{
	if (!HasAuthority())
	{
		return;
	}

	if (!QuantumASC.IsValid())
	{
		return;
	}

	if (DefaultAttributes.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Default attributes are server-authoritative and replicate to clients
	FGameplayEffectContextHandle EffectContext = QuantumASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (int32 Index = 0; Index < DefaultAttributes.Num(); ++Index)
	{
		TSubclassOf<UGameplayEffect> AttributesGE = DefaultAttributes[Index];
		if (!AttributesGE)
		{
			UE_LOG(LogTemp, Error, TEXT("%s() DefaultAttributes[%d] is not valid for %s. Skipping."), *FString(__FUNCTION__), Index, *GetName());
			continue;
		}

		FGameplayEffectSpecHandle NewHandle = QuantumASC->MakeOutgoingSpec(AttributesGE, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = QuantumASC->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), QuantumASC.Get());
		}
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
	
	BindMoveSpeedListener();
	ApplyInitialMoveSpeed();
}

void AQuantumCharacter::BindMoveSpeedListener()
{
	if (!QuantumASC.IsValid() || !QuantumAttributeSet.IsValid())
	{
		return;
	}

	if (MoveSpeedChangedDelegateHandle.IsValid())
	{
		QuantumASC->GetGameplayAttributeValueChangeDelegate(QuantumAttributeSet->GetMoveSpeedAttribute()).Remove(MoveSpeedChangedDelegateHandle);
		MoveSpeedChangedDelegateHandle.Reset();
	}

	MoveSpeedChangedDelegateHandle = QuantumASC->GetGameplayAttributeValueChangeDelegate(QuantumAttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &ThisClass::MoveSpeedChanged);
}

void AQuantumCharacter::ApplyInitialMoveSpeed()
{
	if (!QuantumAttributeSet.IsValid())
	{
		return;
	}

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = QuantumAttributeSet->GetMoveSpeed();
	}
}

void AQuantumCharacter::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = Data.NewValue;
	}
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
