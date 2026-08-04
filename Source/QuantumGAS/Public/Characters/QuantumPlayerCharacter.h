// Fill out your copyright notice in the Description page of Project Settings.

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

UCLASS()
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
	TObjectPtr<UQuantumAbilitySet> AbilitySet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability&Input")
	TObjectPtr<UQuantumInputConfig> InputConfig;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability&Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
protected:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
private:
	void SetDefaultMappingContext() const;
};
