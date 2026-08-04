# Architecture

## Class layout

```
AQuantumGameMode
  └── uses AQuantumPlayerController
  └── uses AQuantumPlayerState
  └── spawns AQuantumPlayerCharacter (via Default Pawn)

AQuantumPlayerState
  └── owns UQuantumASC
  └── owns UQuantumAttributeSet

AQuantumPlayerCharacter : AQuantumCharacter
  └── holds AbilitySet, InputConfig, DefaultMappingContext
  └── camera component
  └── binds input through UQuantumInputComponent

AQuantumPlayerController
  └── PostProcessInput → UQuantumASC::ProcessAbilityInput()
```

---

## Where the ASC lives

The Ability System Component and Attribute Set live on **`AQuantumPlayerState`**.

On possession, the character:

1. Gets the ASC from the player state
2. Calls `InitAbilityActorInfo(PlayerState, Character)`
3. Initializes attributes from `DefaultAttributes`
4. Grants abilities from `AbilitySet`

This keeps the ASC on the player state across pawn changes.

---

## Runtime flow (possession)

```
PossessedBy (server)
  → Get AQuantumPlayerState
  → QuantumASC = PlayerState ASC
  → InitAbilityActorInfo(PS, Character)
  → InitializeAttributes()   // applies DefaultAttributes GE
  → AbilitySet->GiveToAbilitySystem(ASC)
```

On clients, `OnRep_PlayerState` sets up the ASC pointer and attribute init.

---

## Input paths

**Native** (Move, Look, …): hard-coded character functions. No ASC.

```
Enhanced Input
  → UQuantumInputComponent::BindNativeAction
  → AQuantumPlayerCharacter::Move / Look / …
```

**Ability** (Sprint, …): tag forwarded to the ASC.

```
Enhanced Input (press / release)
  → UQuantumInputComponent::BindAbilityActions
  → AQuantumPlayerCharacter::InputAbilityInputTagPressed/Released
  → UQuantumASC::AbilityInputTagPressed/Released   // queues handles
  → AQuantumPlayerController::PostProcessInput
  → UQuantumASC::ProcessAbilityInput
  → TryActivateAbility / AbilitySpecInputReleased
```

See [Input](Input) for the full native vs ability breakdown.

---

## Main classes

| Class | Role |
| --- | --- |
| `AQuantumCharacter` | Base character + `IAbilitySystemInterface`, attribute helpers |
| `AQuantumPlayerCharacter` | Player character: camera, input, ability set grant |
| `AQuantumPlayerState` | Owns ASC and AttributeSet |
| `AQuantumPlayerController` | Forwards input processing to the ASC each frame |
| `AQuantumGameMode` | Base game mode |
| `UQuantumASC` | ASC with input-tag press/release handling |
| `UQuantumAttributeSet` | Health, MaxHealth, HealthRegenRate, MoveSpeed |
| `UQuantumAbilitySet` | Data asset that grants abilities with input tags |
| `UQuantumGameplayAbilityBase` | Ability base with activation policy |
| `UQuantumInputConfig` | Maps Input Actions to gameplay tags |
| `UQuantumInputComponent` | Enhanced Input helpers for native + ability binds |
