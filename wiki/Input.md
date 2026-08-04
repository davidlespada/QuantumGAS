# Input

QuantumGAS uses Enhanced Input. There are two kinds of bindings: **native** and **ability** (non-native).

---

## Native vs ability input

| | Native | Ability (non-native) |
| --- | --- | --- |
| Config array | `NativeInputActions` | `AbilityInputActions` |
| Examples | Move, Look | Sprint, Fire, Jump ability, etc. |
| What happens | Calls a hard-coded function on the character | Forwards an input tag to the ASC |
| Goes through GAS? | No | Yes |
| Bind helper | `BindNativeAction` | `BindAbilityActions` |

### Native

Native inputs are core character controls. They are bound directly to hard-coded functions according to the input (for example `Move` and `Look` on `AQuantumPlayerCharacter`).

The input config still maps an Input Action to a tag so the character can look the action up, but the response is fixed in code: that tag always calls that function. Nothing is granted as an ability, and the ASC is not involved.

Use native for movement, camera, and other always-on controls that should not be Gameplay Abilities.

### Ability (non-native)

Ability inputs are not hard-coded to a specific function per action. Press and release are sent to the ASC with an **input tag**. Any granted ability whose spec has that tag can activate.

The same binding path handles every ability input. Adding a new one is data: Input Action, config entry, ability set entry with matching `InputTag`. No new bind function on the character is required.

Use ability input for anything that should run as a Gameplay Ability (sprint, attacks, skills, and so on).

---

## QuantumInputComponent

`UQuantumInputComponent` extends `UEnhancedInputComponent`.

You must use this class as the player’s input component. The player character casts to it in `SetupPlayerInputComponent`.

Set it in **Project Settings → Input → Default Input Component Class**, or on your character setup.

---

## QuantumInputConfig

`UQuantumInputConfig` is a data asset with two arrays — one for each binding type above.

Each entry is an `InputAction` + `InputTag` pair.

Example from the plugin content: `DA_BaseInputConfig`.

---

## Binding (what the character does)

```cpp
// Ability actions → ASC via tags (one path for all of them)
QuantumInputComponent->BindAbilityActions(
    InputConfig, this,
    &ThisClass::InputAbilityInputTagPressed,
    &ThisClass::InputAbilityInputTagReleased,
    BindHandles);

// Native actions → hard-coded character functions
QuantumInputComponent->BindNativeAction(
    InputConfig, NativeMoveTag, ETriggerEvent::Triggered, this, &ThisClass::Move);

QuantumInputComponent->BindNativeAction(
    InputConfig, NativeLookTag, ETriggerEvent::Triggered, this, &ThisClass::Look);
```

Native binds are one tag → one function.

Ability binds loop every `AbilityInputActions` entry and use:

- `Triggered` → pressed (tag passed to ASC)
- `Completed` → released (tag passed to ASC)

---

## Mapping context

`AQuantumPlayerCharacter` has a `DefaultMappingContext` property.

In `BeginPlay` it adds that context to the local player’s Enhanced Input subsystem.

Example asset: `IMC_Default` (maps `IA_Move`, `IA_Look`, `IA_Sprint` to keys/axes).

Move and Look are native. Sprint is an ability input.

---

## Adding a native input

1. Create an Input Action and add it to the mapping context.
2. Add it under **Native Input Actions** in the input config with a tag.
3. Declare the tag if needed (see [Gameplay Tags](Gameplay-Tags.md)).
4. In `SetupPlayerInputComponent`, call `BindNativeAction` with that tag and your function.

```cpp
QuantumInputComponent->BindNativeAction(
    InputConfig, YourNativeTag, ETriggerEvent::Triggered, this, &ThisClass::YourFunction);
```

---

## Adding an ability input

1. Create an Input Action (e.g. `IA_Fire`) and add it to the mapping context.
2. Add an entry under **Ability Input Actions** in the input config with a tag (e.g. `Input.Fire`).
3. When granting the ability in a `UQuantumAbilitySet`, set the same tag on **InputTag**.

No extra bind call is needed on the character if `BindAbilityActions` is already set up. The ASC matches abilities by that tag on the ability spec (`DynamicSpecSourceTags`).

---

## Ability processing order

Ability input is not activated only in the press callback. The ASC queues pressed/released handles, then `AQuantumPlayerController::PostProcessInput` calls `ProcessAbilityInput` each frame.

That supports both one-shot and hold-to-activate abilities. See [Abilities](Abilities.md).

Native input does not use this path; it runs the bound function when Enhanced Input fires.
