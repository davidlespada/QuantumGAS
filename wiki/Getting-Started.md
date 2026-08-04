# Getting Started

## Installation

1. Copy the `QuantumGAS` folder into your project's `Plugins/` directory.
2. Open the project and rebuild when prompted.
3. Confirm the plugin is enabled under **Edit → Plugins**.

`GameplayAbilities` and `EnhancedInput` are declared as dependencies in the `.uplugin` and should enable automatically.

> **Blueprint-only projects:** add at least one C++ class first so Unreal creates the build files, then add the plugin.

---

## Setup

The included blueprints already wire GAS and input. You only need two steps:

### 1. Game Mode

Set the level (or World Settings) Game Mode to `GM_Default`.

That game mode uses the plugin’s player character, player controller, and player state classes.

### 2. Input component

Use `QuantumInputComponent` instead of the default input component.

You can set this in:

- **Project Settings → Input → Default Input Component Class**, or
- on the character / controller if you override it there

`AQuantumPlayerCharacter::SetupPlayerInputComponent` casts to `UQuantumInputComponent` and will fail if a different component is used.

---

## Verify

1. Open `Lv_Empty` from the plugin content.
2. Play in editor.
3. You should be able to move, look, and sprint.

If input does nothing, check that `QuantumInputComponent` is set and that the mapping context is applied (the example character does this in `BeginPlay`).

---

## What the example already has

| Piece | Asset / class |
| --- | --- |
| Game mode | `GM_Default` |
| Character | `BP_PlayerCharacter` (`AQuantumPlayerCharacter`) |
| Input config | `DA_BaseInputConfig` |
| Mapping context | `IMC_Default` |
| Ability set | `DA_PlayerAbilitySet` |
| Attribute init | `GE_PlayerAttributeInit` |
| Sprint | `GA_Sprint` |

You can subclass these or replace them with your own assets. See the other wiki pages for how each part works.
