# QuantumGAS

Lightweight Gameplay Ability System setup for Unreal Engine 5, with Enhanced Input support.

The goal of this plugin is to save some of the boilerplate needed to set up GAS, and to provide a minimal base for a controllable character with GAS compatibility.

**UE 5.8** · MIT · David L. Espada

---

## What's included

- Character / PlayerCharacter with ASC
- PlayerController, PlayerState, GameMode, GameInstance
- Attribute set (Health, MaxHealth, MoveSpeed, etc.)
- Ability set data asset and a sprint ability example
- Enhanced Input through `QuantumInputComponent`

---

## Install

1. (For GitHub) This uses Git LFS. Make sure to have it installed. Do not click "Download ZIP". Do the usual git clone for LFS to work. 
2. Copy the folder into `YourProject/Plugins/QuantumGAS`
3. Open the project and rebuild if prompted
4. Enable the plugin if needed (`Edit → Plugins`)

---

## Setup

The blueprints already include the GAS and input configuration. You only need to:

1. Set the level Game Mode to `GM_Default`
2. Use `QuantumInputComponent` as the input component (Project Settings → Input → Default Input Component Class)

---

## Documentation

For more detail, code snippets, and how the systems fit together, see the [Wiki](wiki/Home.md).

---

## Contributing

Contributions are welcome for fixes and improvements to what already exists.

Please do not add new systems or extra features. This plugin is meant to stay lightweight.

See [CONTRIBUTING.md](CONTRIBUTING.md).

---

## License

[MIT](LICENSE)
