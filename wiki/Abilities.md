# Abilities

---

## Ability base

`UQuantumGameplayAbilityBase` extends `UGameplayAbility` and adds an activation policy:

| Policy | Behavior |
| --- | --- |
| `OnInputTriggered` | Activate once when the input is pressed |
| `WhileInputActive` | Keep trying to activate while the input is held |

`UQuantumASC::ProcessAbilityInput` reads this policy when deciding what to activate.

Example subclass: `UQuantumSprintGameplayAbility` / content blueprint `GA_Sprint`.

---

## Ability sets

`UQuantumAbilitySet` is a data asset that grants a list of abilities to an ASC.

Each entry has:

| Field | Meaning |
| --- | --- |
| `GameplayAbility` | Subclass of `UQuantumGameplayAbilityBase` |
| `AbilityLevel` | Level passed into the ability spec |
| `InputTag` | Tag stored on the spec for input routing |

`GiveToAbilitySystem` only runs on the authority (server). It:

1. Builds an `FGameplayAbilitySpec` for each entry
2. Adds `InputTag` to `DynamicSpecSourceTags`
3. Calls `GiveAbility`

Example asset: `DA_PlayerAbilitySet`.

The player character grants its `AbilitySet` in `PossessedBy`.

---

## Adding a new ability

### 1. Create the ability class

```cpp
UCLASS()
class UGA_Fire : public UQuantumGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UGA_Fire()
	{
		ActivationPolicy = EQuantumAbilityActivationPolicy::OnInputTriggered;
	}

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
};
```

Or create a Blueprint ability based on `QuantumGameplayAbilityBase` / `QuantumSprintGameplayAbility`.

### 2. Wire input

1. Input Action + mapping context entry
2. `AbilityInputActions` entry in your input config with a tag
3. Same tag on the ability set entry’s `InputTag`

### 3. Grant it

Add the ability to a `UQuantumAbilitySet` and assign that set on the character’s `AbilitySet` property (or grant the set from code).

---

## Input routing on the ASC

```
AbilityInputTagPressed(Tag)
  → find specs whose DynamicSpecSourceTags contain Tag
  → queue in InputPressedSpecHandles / InputHeldSpecHandles

AbilityInputTagReleased(Tag)
  → queue in InputReleasedSpecHandles
  → remove from InputHeldSpecHandles

ProcessAbilityInput (from PlayerController)
  → WhileInputActive + held → activate
  → OnInputTriggered + pressed → activate
  → released → AbilitySpecInputReleased
  → clear pressed/released queues
```

If an ability has no matching `InputTag` on the spec, input will not activate it.

---

## Sprint example

Content path: `GA_Sprint` + `GE_SprintSpeed`.

Typical setup for a hold ability:

- Activation policy: `WhileInputActive`
- Input tag: `Input.Sprint` (see [Gameplay Tags](Gameplay-Tags.md))
- Granted through `DA_PlayerAbilitySet`
