// Copyright (c) 2026 David L. Espada. All Rights Reserved.


#include "GAS/Attributes/QuantumAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UQuantumAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UQuantumAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQuantumAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQuantumAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQuantumAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UQuantumAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQuantumAttributeSet, Health, OldHealth);
}

void UQuantumAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQuantumAttributeSet, MaxHealth, OldMaxHealth);
}

void UQuantumAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQuantumAttributeSet, HealthRegenRate, OldHealthRegenRate);
}

void UQuantumAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQuantumAttributeSet, MoveSpeed, OldMoveSpeed);
}
