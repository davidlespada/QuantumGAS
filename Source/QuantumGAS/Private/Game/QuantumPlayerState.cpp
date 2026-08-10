// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/QuantumPlayerState.h"

#include "GAS/QuantumASC.h"
#include "GAS/Attributes/QuantumAttributeSet.h"

AQuantumPlayerState::AQuantumPlayerState()
{
	QuantumAsc = CreateDefaultSubobject<UQuantumASC>(TEXT("QuantumASC"));
	QuantumAsc->SetIsReplicated(true);
	QuantumAsc->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	SetNetUpdateFrequency(100.0f);
	
	QuantumAttributeSet = CreateDefaultSubobject<UQuantumAttributeSet>(TEXT("QuantumAttributeSet"));
}

void AQuantumPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	if (QuantumAsc)
	{
		OnHealthChangedDelegateHandle = QuantumAsc->GetGameplayAttributeValueChangeDelegate(QuantumAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);
	}
}

void AQuantumPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
}

void AQuantumPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

UAbilitySystemComponent* AQuantumPlayerState::GetAbilitySystemComponent() const
{
	return QuantumAsc;
}

UQuantumAttributeSet* AQuantumPlayerState::GetAttributeSet() const
{
	return QuantumAttributeSet;
}

float AQuantumPlayerState::GetHealth() const
{
	return QuantumAttributeSet->GetHealth();
}

bool AQuantumPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}
