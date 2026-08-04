# Attributes

---

## QuantumAttributeSet

`UQuantumAttributeSet` lives on `AQuantumPlayerState` next to the ASC.

| Attribute | Category | Replicated |
| --- | --- | --- |
| `Health` | Health | Yes |
| `MaxHealth` | Health | Yes |
| `HealthRegenRate` | Health | Yes |
| `MoveSpeed` | Movement | Yes |

Accessors are provided via the usual `ATTRIBUTE_ACCESSORS` macros (`GetHealth()`, `SetHealth()`, etc.).

---

## Initialization

Characters have a `DefaultAttributes` property: a Gameplay Effect class used to set starting values.

`AQuantumCharacter::InitializeAttributes` applies that GE to the ASC (server and client).

Example content: `GE_PlayerAttributeInit` on `BP_PlayerCharacter`.

If `DefaultAttributes` is missing, initialization logs an error and skips.

---

## Move speed

On `BeginPlay`, `AQuantumCharacter` binds to MoveSpeed changes.

When MoveSpeed changes, `MaxWalkSpeed` on the character movement component is updated to the new value.

Abilities or effects that modify MoveSpeed (for example sprint) will affect movement automatically once that binding is active.

---

## Reading attributes

From the character:

```cpp
float HP = Character->GetHealth();
bool bAlive = Character->IsAlive();  // Health > 0
```

From the player state:

```cpp
float HP = PlayerState->GetHealth();
UQuantumAttributeSet* Set = PlayerState->GetAttributeSet();
```

---

## Extending the attribute set

For small projects you can add properties directly to `UQuantumAttributeSet` (or a subclass):

```cpp
UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
FGameplayAttributeData Stamina;
ATTRIBUTE_ACCESSORS(UQuantumAttributeSet, Stamina)
```

Then:

1. Implement `OnRep_Stamina` and register replication in `GetLifetimeReplicatedProps`
2. Include the attribute in your init Gameplay Effect
3. Make sure the set is still created on the player state (subclass PS if you use a different set class)

Keep changes minimal if you want to stay aligned with the plugin’s lightweight scope. Prefer project-side subclasses over growing the plugin attribute set when possible.
