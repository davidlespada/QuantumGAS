# QuantumGAS Wiki

QuantumGAS is a lightweight Gameplay Ability System setup for Unreal Engine 5, with Enhanced Input support.

The goal is to save some of the boilerplate needed to set up GAS, and to provide a minimal base for a controllable character with GAS compatibility.

---

## Pages

| Topic | Page |
| --- | --- |
| Install and basic setup | [Getting Started](Getting-Started.md) |
| How the classes fit together | [Architecture](Architecture.md) |
| Enhanced Input binding | [Input](Input.md) |
| Abilities and ability sets | [Abilities](Abilities.md) |
| Health, speed, and attributes | [Attributes](Attributes.md) |
| Native gameplay tags | [Gameplay Tags](Gameplay-Tags.md) |

---

## Requirements

| Item | Version |
| --- | --- |
| Unreal Engine | 5.8 |
| Plugins | `GameplayAbilities`, `EnhancedInput` |

---

## Content overview

| Asset | Path | Role |
| --- | --- | --- |
| `GM_Default` | `Content/Blueprints/Game/` | Example game mode |
| `BP_PlayerCharacter` | `Content/Blueprints/Player/` | Example player character |
| `DA_BaseInputConfig` | `Content/Blueprints/Input/` | Input action → tag map |
| `IMC_Default` | `Content/Blueprints/Input/Maps/` | Default mapping context |
| `DA_PlayerAbilitySet` | `Content/Blueprints/Player/GAS/` | Granted abilities |
| `GE_PlayerAttributeInit` | `Content/Blueprints/Player/GAS/Effects/` | Attribute init effect |
| `GA_Sprint` | `Content/Blueprints/GAS/Abilities/` | Sprint ability example |
| `Lv_Empty` | `Content/Maps/` | Sample map |
