// Copyright (c) 2026 David L. Espada. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "QuantumPlayerState.generated.h"

struct FOnAttributeChangeData;
class UQuantumAttributeSet;
class UQuantumASC;
/**
 * 
 */
UCLASS()
class QUANTUMGAS_API AQuantumPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	AQuantumPlayerState();
	
protected:
	UPROPERTY()
	TObjectPtr<UQuantumASC> QuantumAsc;
	
	UPROPERTY()
	TObjectPtr<UQuantumAttributeSet> QuantumAttributeSet;
	
	virtual void BeginPlay() override;
	
	FDelegateHandle OnHealthChangedDelegateHandle;
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	FDelegateHandle OnMaxHealthChangedDelegateHandle;
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UQuantumAttributeSet* GetAttributeSet() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Player State")
	bool IsAlive() const;
};
