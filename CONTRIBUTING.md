# Contributing

This plugin is meant to stay lightweight. Contributions should improve or fix what already exists, not add new systems.

## Welcome

- Bug fixes
- Cleanups and small improvements
- Documentation updates

## Not welcome

- New feature systems
- Extra modules or optional add-ons

If you are unsure whether a change fits, open an issue first.

## Process

1. Fork the repo
2. Put the plugin in a test project's `Plugins/` folder
3. Make changes on a branch
4. Test (PIE at minimum; Standalone / multiplayer if you touch replication)
5. Open a PR describing what changed and why

## Notes

- Follow Epic's C++ style where reasonable
- Keep GAS replication correct
- Do not commit `Binaries/`, `Intermediate/`, or `Saved/`
