// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QuantumPlayerController.generated.h"

class UQuantumASC;
/**
 * 
 */
UCLASS()
class QUANTUMGAS_API AQuantumPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void AcknowledgePossession(class APawn* P) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	
private:
	UQuantumASC* GetQuantumASC() const;
};
