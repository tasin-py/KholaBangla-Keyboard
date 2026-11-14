# Authors and credits

## KholaBangla Keyboard

KholaBangla Keyboard is developed by **[tasin-py](https://github.com/tasin-py)**.

## Based on OpenBangla Keyboard

KholaBangla Keyboard is a modified version of **[OpenBangla Keyboard](https://github.com/OpenBangla/OpenBangla-Keyboard)**,
created by **Muhammad Mominul Huque** with many contributors, and used under the terms of the
GNU General Public License, version 3 or later.

The original copyright notices are kept in the source files. Contributors to the original code include
Muhammad Mominul Huque, CSSlayer (Fcitx5 support) and the other
[OpenBangla Keyboard contributors](https://github.com/OpenBangla/OpenBangla-Keyboard/graphs/contributors).

### What KholaBangla changed

Starting on 15 November 2026 from the OpenBangla Keyboard development version (3.0.0, `develop` branch),
KholaBangla Keyboard:

- renamed the application, its packages, input method engines and files to KholaBangla Keyboard, with a new logo;
- removed the Windows and macOS ports to focus on Linux;
- added a one-command installer for Ubuntu, Debian, Kali, Fedora, openSUSE, Arch and their derivatives;
- made package installation safe without a desktop session, and added Qt SVG to the package dependencies;
- added a check for updates with one-click update;
- added its own build, test and release workflows.

## Third-party components

- **riti**, the Bangla typing engine, in `src/engine/riti`: Mozilla Public License 2.0 (see its `LICENSE`).
- **Corrosion**, the CMake–Rust integration, in `cmake/corrosion-rs`: MIT License (see its `LICENSE`).
- **Kalpurush**, the Bangla font in `data/kalpurush.ttf`.
- The **Avro Phonetic** typing scheme by [OmicronLab](https://www.omicronlab.com/avro-keyboard.html).
