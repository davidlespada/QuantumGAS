// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/QuantumAbilitySet.h"

#include "GameplayAbilitySpecHandle.h"
#include "GAS/QuantumASC.h"
#include "GAS/Abilities/QuantumGameplayAbilityBase.h"

void FQuantumAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void UQuantumAbilitySet::GiveToAbilitySystem(UQuantumASC* InASC, FQuantumAbilitySet_GrantedHandles* OutGrantedHandles,
	UObject* SourceObject) const
{
	check(InASC);
	
	if (!InASC->IsOwnerActorAuthoritative())
	{
		return;
	}
	
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FQuantumAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];
		
		if (!IsValid(AbilityToGrant.GameplayAbility))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}
		
		UQuantumGameplayAbilityBase* AbilityCDO = AbilityToGrant.GameplayAbility.GetDefaultObject();
		
		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);
		
		const FGameplayAbilitySpecHandle Handle = InASC->GiveAbility(AbilitySpec);
		
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(Handle);
		}
	}
}
