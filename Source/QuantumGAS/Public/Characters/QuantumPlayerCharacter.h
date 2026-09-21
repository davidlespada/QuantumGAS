// Copyright (c) 2026 David L. Espada. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "QuantumCharacter.h"
#include "QuantumPlayerCharacter.generated.h"

class UCameraComponent;
struct FGameplayTag;
class UInputMappingContext;
class UQuantumInputConfig;
class UQuantumAbilitySet;

UCLASS(meta = (PrioritizeCategories = "Ability&Input"))
class QUANTUMGAS_API AQuantumPlayerCharacter : public AQuantumCharacter
{
	GENERATED_BODY()

public:
	AQuantumPlayerCharacter();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void InputAbilityInputTagPressed(FGameplayTag InputTag);
	void InputAbilityInputTagReleased(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability&Input")
	TArray<TObjectPtr<UQuantumAbilitySet>> AbilitySets;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability&Input")
	TArray<TObjectPtr<UQuantumInputConfig>> InputConfigs;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability&Input")
	TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

protected:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	
private:
	void SetDefaultMappingContext() const;
};
