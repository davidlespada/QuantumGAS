// Copyright Quantum. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GAS/Attributes/QuantumAttributeSet.h"
#include "QuantumCharacter.generated.h"

class UQuantumAttributeSet;
class UQuantumASC;

UCLASS()
class QUANTUMGAS_API AQuantumCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	TWeakObjectPtr<UQuantumASC> QuantumASC;
	TWeakObjectPtr<UQuantumAttributeSet> QuantumAttributeSet;
	
	virtual void InitializeAttributes();
	
	FDelegateHandle MoveSpeedChangedDelegateHandle;
	virtual void MoveSpeedChanged(const FOnAttributeChangeData& Data);


public:
	AQuantumCharacter();
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;
	
	/**
	 * Getters for attributes
	 **/
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const;
	
};
