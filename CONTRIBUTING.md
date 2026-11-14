# Contributing to KholaBangla Keyboard

Thank you for helping make KholaBangla Keyboard better! Bug reports, fixes, new layouts, packaging
improvements, documentation and translations are all welcome.

## Reporting a problem

[Open an issue](https://github.com/tasin-py/KholaBangla/issues) and include:

- your Linux distribution and version (`cat /etc/os-release`),
- your desktop (GNOME, KDE Plasma, …) and input method framework (IBus or Fcitx5),
- the KholaBangla Keyboard version, and what you expected to happen.

## Making a change

1. Fork the repository and create a branch from `main`.
2. Build it (see [Building from source](README.md#building-from-source)).
3. Make your change and test it. If you change `tools/install.sh`, also run
   `bash tools/test-install.sh` and `shellcheck tools/install.sh`.
4. Open a pull request against `main` describing what you changed and how you tested it.

Please follow the [Code of Conduct](CODE_OF_CONDUCT.md).

## Releasing

Releases are made by pushing a tag that matches `version.txt` (for example `1.0.1`). The
[Release workflow](.github/workflows/release.yml) builds the packages for every supported
distribution and publishes them on the Releases page, where the installer finds them.
