// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "QuantumAbilitySet.generated.h"

struct FGameplayAbilitySpecHandle;
class UQuantumASC;
class UQuantumGameplayAbilityBase;

USTRUCT(BlueprintType)
struct FQuantumAbilitySet_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuantumGameplayAbilityBase> GameplayAbility;
	
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FQuantumAbilitySet_GrantedHandles
{
	GENERATED_BODY()
	
public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	
protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
};

UCLASS()
class QUANTUMGAS_API UQuantumAbilitySet : public UDataAsset
{
	GENERATED_BODY()
public:
	void GiveToAbilitySystem(UQuantumASC* InASC, FQuantumAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TArray<FQuantumAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};
