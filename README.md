<p align="right"><a href="README.bn.md"><b>বাংলায় পড়ুন</b></a></p>

<p align="center">
  <img src="data/128.png" alt="KholaBangla Keyboard logo" width="128">
</p>

<h1 align="center">KholaBangla Keyboard</h1>

<h3 align="center">Type Bangla on Linux, the way you type it on Avro. Installed with one command.</h3>

<p align="center">
  <a href="https://github.com/tasin-py/KholaBangla/releases"><img src="https://img.shields.io/github/v/release/tasin-py/KholaBangla?label=release" alt="Latest release"></a>
  <a href="https://github.com/tasin-py/KholaBangla/actions/workflows/ci.yml"><img src="https://github.com/tasin-py/KholaBangla/actions/workflows/ci.yml/badge.svg" alt="CI status"></a>
  <a href="LICENSE"><img src="https://img.shields.io/badge/license-GPL--3.0-blue.svg" alt="License: GPL-3.0"></a>
</p>

**KholaBangla Keyboard** is a free, open-source Bangla input method for Linux. It includes **Avro Phonetic**
with dictionary suggestions and autocorrect, the popular fixed layouts (Probhat, Munir Optima,
National/Jatiya, Bornona, Avro Easy, Khipro) and typing automation tools. It works with both
**IBus** and **Fcitx5**, and sets itself up on GNOME, KDE Plasma, Cinnamon, XFCE, MATE, Budgie, LXQt and Deepin.

## Contents

- [Install](#install)
- [Supported distributions](#supported-distributions)
- [Installer options](#installer-options)
- [Using KholaBangla Keyboard](#using-kholabangla-keyboard)
- [Features](#features)
- [Uninstall](#uninstall)
- [Troubleshooting](#troubleshooting)
- [Building from source](#building-from-source)
- [Support the project](#support-the-project)
- [Credits](#credits)
- [License](#license)

## Install

Open a terminal, paste this **one command**, and press <kbd>Enter</kbd>:

```bash
bash -c "$(curl -fsSL https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh 2>/dev/null || wget -qO- https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh)"
```

That's it. The installer:

1. detects your Linux distribution, version and processor,
2. downloads and installs the right package from the newest KholaBangla release,
3. installs the input method framework (IBus or Fcitx5) that suits your desktop,
4. adds **KholaBangla Keyboard** to your input sources.

It asks for confirmation once, and for your password when it needs administrator rights.
It never replaces an input method you already use (for example Fcitx for Chinese or Japanese).
When it's done, **log out and log back in**, then switch between English and Bangla with
<kbd>Super</kbd>+<kbd>Space</kbd> (GNOME) or <kbd>Ctrl</kbd>+<kbd>Space</kbd> (Fcitx5 desktops).

> [!TIP]
> Want to see what it would do first? Add `-- --dry-run` at the end of the command.

## Supported distributions

| Distribution | Versions |
|---|---|
| Ubuntu | 22.04 and newer |
| Ubuntu-based: Linux Mint, Pop!\_OS, Zorin OS, elementary OS, KDE neon, … | Based on Ubuntu 22.04 or newer |
| Debian | 12 (Bookworm) and newer |
| Debian-based: Kali Linux, Parrot OS, MX Linux, LMDE, … | Current releases |
| Fedora (and Nobara) | 41 and newer |
| openSUSE | Tumbleweed |
| Arch Linux, Manjaro, EndeavourOS, … | Rolling |

Packages are built for 64-bit Intel/AMD (`x86_64`) and 64-bit ARM (`aarch64`) computers
(Arch Linux: `x86_64` only). On anything else, [build from source](#building-from-source).

## Installer options

Add the options after `--` at the end of the install command, or run the script directly (`bash install.sh [options]`):

| Option | What it does |
|---|---|
| `--ibus` | Use the IBus framework (best on GNOME and Cinnamon) |
| `--fcitx5` | Use the Fcitx5 framework (best on KDE Plasma) |
| `--no-setup` | Only install the package; don't configure the desktop |
| `--dry-run` | Show what would happen without changing anything |
| `-y`, `--yes` | Don't ask for confirmation |
| `--uninstall` | Remove KholaBangla Keyboard |
| `-h`, `--help` | Show help |

## Using KholaBangla Keyboard

- **Switch language:** <kbd>Super</kbd>+<kbd>Space</kbd> on GNOME (IBus), <kbd>Ctrl</kbd>+<kbd>Space</kbd> with Fcitx5, or the shortcut in your desktop's input settings.
- **Choose a layout:** click the KholaBangla icon in the top bar, or open **KholaBangla Keyboard** from your app menu.
- **Avro Phonetic:** type Bangla using English letters, for example `ami banglay gan gai` → `আমি বাংলায় গান গাই`.
  Suggestions appear as you type; press <kbd>Space</kbd> or <kbd>Enter</kbd> to accept.

## Features

**Avro Phonetic**
- 100% compatible with the Avro Phonetic scheme.
- Dictionary suggestions for correctly spelled words as you type.
- Autocorrect for many commonly mistyped words, and your own autocorrect entries.
- Common English words (Facebook, download, …) are written in Bangla even with their English spelling.
- A preview window right under the cursor.

**Fixed keyboard layouts**
- Probhat, Munir Optima, Avro Easy, Bornona, National (Jatiya) and Khipro, out of the box.
- Supports Avro Keyboard layout files (version 5).
- Automatic vowel forming, old-style *Reph*, traditional *-Kar* joining and *Chandrabindu* position fixing.

**Convenience**
- Avro-style **Top Bar** for quick configuration, and a built-in **Layout Viewer**.
- Follows your system's light or dark theme.
- Sets itself up in your desktop's input sources.

## Uninstall

```bash
bash -c "$(curl -fsSL https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh 2>/dev/null || wget -qO- https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh)" -- --uninstall
```

Or remove the `kholabangla-keyboard` package with your package manager.

## Troubleshooting

**KholaBangla Keyboard doesn't show up in my input sources.**
Log out and log back in (or restart) after installing; the input method framework only starts with a new session.
On GNOME, open *Settings → Keyboard → Input Sources → +* and look under *Bangla*.

**I can't type Bangla in some applications.**
Make sure the input method framework is running (`ibus-daemon -drx` for IBus, `fcitx5 -d` for Fcitx5) and that your
session has the matching `GTK_IM_MODULE`, `QT_IM_MODULE` and `XMODIFIERS` settings.

**KDE Plasma on Wayland.**
Open *System Settings → Keyboard → Virtual Keyboard* and choose *Fcitx 5*.

**"Couldn't recognise your Linux distribution".**
Please [open an issue](https://github.com/tasin-py/KholaBangla/issues) with the output of `cat /etc/os-release`.
In the meantime, you can [build from source](#building-from-source).

## Building from source

Install the build tools for your distribution:

| Distribution | Command |
|---|---|
| Ubuntu / Debian | `sudo apt install build-essential cmake ninja-build rustc cargo libibus-1.0-dev libfcitx5core-dev libzstd-dev qtbase5-dev qtbase5-dev-tools libqt5svg5-dev` |
| Fedora | `sudo dnf install @buildsys-build cmake ninja-build rust cargo ibus-devel fcitx5-devel libzstd-devel qt5-qtdeclarative-devel qt5-qtsvg-devel` |
| Arch Linux | `sudo pacman -S base-devel cmake ninja rust libibus fcitx5 zstd qt5-base qt5-svg` |
| openSUSE | `sudo zypper install cmake ninja rust ibus-devel fcitx5-devel libzstd-devel libQt5Core-devel libQt5Widgets-devel libQt5Network-devel libQt5Svg-devel gcc gcc-c++` |

Then build and install:

```bash
git clone https://github.com/tasin-py/KholaBangla.git
cd KholaBangla
cmake -S . -B build -GNinja -DCMAKE_INSTALL_PREFIX=/usr -DENABLE_BOTH=ON
ninja -C build
sudo ninja -C build install
```

Use `-DENABLE_IBUS=ON` or `-DENABLE_FCITX=ON` instead of `-DENABLE_BOTH=ON` to build only one of them.

## Support the project

If KholaBangla Keyboard helps you, you can support its development:

- ☕ **Support tasin-py**: [supportkori.com/tasinpy](https://www.supportkori.com/tasinpy)
- ⭐ **Star this repository** so more people can find it.
- 📣 **Tell your friends** who want to type Bangla on Linux.

## Credits

KholaBangla Keyboard is based on **[OpenBangla Keyboard](https://github.com/OpenBangla/OpenBangla-Keyboard)**
by **Muhammad Mominul Huque** and its contributors, used under the GNU GPL v3. See [AUTHORS.md](AUTHORS.md) for details.

It also builds on:
- **riti**, the Bangla typing engine (Mozilla Public License 2.0), in `src/engine/riti`;
- the **Avro Phonetic** scheme by OmicronLab;
- the **Kalpurush** font.

## License

KholaBangla Keyboard is free software, released under the [GNU General Public License v3.0](LICENSE) or later.
