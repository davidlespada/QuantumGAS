// Copyright (c) 2026 David L. Espada. All Rights Reserved.


#include "Characters/QuantumPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Game/QuantumPlayerController.h"
#include "Game/QuantumPlayerState.h"
#include "GAS/QuantumAbilitySet.h"
#include "GAS/QuantumASC.h"
#include "Input/QuantumInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Tags/QuantumAbilityTags.h"


// Sets default values
AQuantumPlayerCharacter::AQuantumPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Base class owns the camera but deliberately leaves it unattached here;
	// derived per-mode characters perform the one explicit attachment
	// (FP mesh head socket, capsule for no-mesh, spring arm for third person).
	// Note: a scene component without an explicit attachment auto-attaches to the RootComponent.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
}

// Called when the game starts or when spawned
void AQuantumPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetDefaultMappingContext();
}

void AQuantumPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AQuantumPlayerState* QuantumPlayerState = GetPlayerState<AQuantumPlayerState>();
	if (IsValid(QuantumPlayerState))
	{
		QuantumASC = Cast<UQuantumASC>(QuantumPlayerState->GetAbilitySystemComponent());
		if (QuantumASC.IsValid())
		{
			QuantumASC->InitAbilityActorInfo(QuantumPlayerState, this);
			QuantumAttributeSet = QuantumPlayerState->GetAttributeSet();
			InitializeAttributes();
			BindMoveSpeedListener();
			ApplyInitialMoveSpeed();
		}
	}
	SetOwner(NewController);
	
	if (QuantumASC.IsValid())
	{
		for (const TObjectPtr<UQuantumAbilitySet>& AbilitySet : AbilitySets)
		{
			if (IsValid(AbilitySet))
			{
				AbilitySet->GiveToAbilitySystem(QuantumASC.Get(), nullptr, this);
			}
		}
	}
}

void AQuantumPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	AQuantumPlayerState* QuantumPlayerState = GetPlayerState<AQuantumPlayerState>();
	if (IsValid(QuantumPlayerState))
	{
		QuantumASC = Cast<UQuantumASC>(QuantumPlayerState->GetAbilitySystemComponent());
		if (QuantumASC.IsValid())
		{
			QuantumASC->InitAbilityActorInfo(QuantumPlayerState, this);
			QuantumAttributeSet = QuantumPlayerState->GetAttributeSet();
			BindMoveSpeedListener();
			ApplyInitialMoveSpeed();
		}
	}
}

// Called every frame
void AQuantumPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AQuantumPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UQuantumInputComponent* QuantumInputComponent = Cast<UQuantumInputComponent>(PlayerInputComponent);
	check(QuantumInputComponent);
	
	TArray<uint32> BindHandles;
	
	FGameplayTag NativeMoveTag = QuantumAbilityTags::Input_Move;
	FGameplayTag NativeLookTag = QuantumAbilityTags::Input_Look;
	
	for (const TObjectPtr<UQuantumInputConfig>& InputConfig : InputConfigs)
	{
		if (!IsValid(InputConfig))
		{
			continue;
		}

		QuantumInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::InputAbilityInputTagPressed,
		                                          &ThisClass::InputAbilityInputTagReleased, BindHandles);
	
		QuantumInputComponent->BindNativeAction(InputConfig, NativeMoveTag, ETriggerEvent::Triggered, this, &ThisClass::Move);
		QuantumInputComponent->BindNativeAction(InputConfig, NativeLookTag, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AQuantumPlayerCharacter::InputAbilityInputTagPressed(FGameplayTag InputTag)
{
	if (QuantumASC.IsValid())
	{
		QuantumASC->AbilityInputTagPressed(InputTag);
	}
}

void AQuantumPlayerCharacter::InputAbilityInputTagReleased(FGameplayTag InputTag)
{
	if (QuantumASC.IsValid())
	{
		QuantumASC->AbilityInputTagReleased(InputTag);
	}
}

void AQuantumPlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	if(GetController())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardVector, DirectionValue.Y);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, DirectionValue.X);
	}
}

void AQuantumPlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	if(GetController())
	{
		if(LookValue.X != 0.0f)
		{
			AddControllerYawInput(LookValue.X);
		}

		if(LookValue.Y != 0.0f)
		{
			AddControllerPitchInput(-LookValue.Y);
		}
	}
}

void AQuantumPlayerCharacter::SetDefaultMappingContext() const
{
	if (DefaultMappingContexts.IsEmpty())
	{
		return;
	}

	if (AQuantumPlayerController* PC = Cast<AQuantumPlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			for (int32 Index = 0; Index < DefaultMappingContexts.Num(); ++Index)
			{
				if (IsValid(DefaultMappingContexts[Index].Get()))
				{
					Subsystem->AddMappingContext(DefaultMappingContexts[Index], Index);
				}
			}
		}
	}
}
