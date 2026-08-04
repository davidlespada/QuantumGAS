# Gameplay Tags

Native tags are declared in `QuantumAbilityTags`:

| C++ name | Tag string | Used for |
| --- | --- | --- |
| `Input_Move` | `Input.Move` | Native move binding |
| `Input_Look` | `Input.Look` | Native look binding |
| `Input_Sprint` | `Input.Sprint` | Sprint ability input |

Defined in:

- `Source/QuantumGAS/Public/Tags/QuantumAbilityTags.h`
- `Source/QuantumGAS/Private/Tags/QuantumAbilityTags.cpp`

---

## Usage

Native tags in character setup:

```cpp
FGameplayTag NativeMoveTag = QuantumAbilityTags::Input_Move;
FGameplayTag NativeLookTag = QuantumAbilityTags::Input_Look;
```

Ability tags are usually set on:

1. `UQuantumInputConfig` → `AbilityInputActions`
2. `UQuantumAbilitySet` → entry `InputTag`

Both sides must use the same tag string.

---

## Adding tags

In C++:

```cpp
// .h
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Fire)

// .cpp
UE_DEFINE_GAMEPLAY_TAG(Input_Fire, "Input.Fire")
```

Or add tags in the editor (**Project Settings → Gameplay Tags**) and reference them from data assets without a native declaration.

For ability input, the important part is that the input config tag and the ability set tag match.
