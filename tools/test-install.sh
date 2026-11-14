#!/usr/bin/env bash
# Tests for tools/install.sh distribution detection and package selection.
#
# Each case feeds the installer a fake /etc/os-release (through OB_OS_RELEASE)
# and a fixed list of release packages (OB_ASSETS), runs it with --dry-run and
# checks which package it picks. Nothing is downloaded or installed.
#
# Usage: bash tools/test-install.sh

set -u
HERE="$(cd "$(dirname "$0")" && pwd)"
INSTALLER="$HERE/install.sh"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

V="1.0.0"
P="kholabangla-keyboard_$V"
export OB_VERSION="$V"
export OB_ASSETS="$P-archlinux-x86_64.pkg.tar.zst
$P-debian12_amd64.deb
$P-debian12_arm64.deb
$P-debian13_amd64.deb
$P-debian13_arm64.deb
$P-fedora41.aarch64.rpm
$P-fedora41.x86_64.rpm
$P-fedora42.aarch64.rpm
$P-fedora42.x86_64.rpm
$P-opensuse-tumbleweed.aarch64.rpm
$P-opensuse-tumbleweed.x86_64.rpm
$P-ubuntu22.04_amd64.deb
$P-ubuntu22.04_arm64.deb
$P-ubuntu24.04_amd64.deb
$P-ubuntu24.04_arm64.deb"
export OB_ARCH=x86_64

pass=0; fail=0
ok()  { pass=$((pass + 1)); printf '  ok    %s\n' "$1"; }
bad() { fail=$((fail + 1)); printf '  FAIL  %s\n' "$1"; }

# check <name> <expected package or "UNSUPPORTED"> <os-release content>
check() {
  local name="$1" expected="$2" out got
  printf '%s\n' "$3" > "$TMP/os-release"
  out=$(OB_OS_RELEASE="$TMP/os-release" bash "$INSTALLER" --dry-run --yes --no-setup 2>&1)
  if printf '%s\n' "$out" | grep -q '^Error:'; then
    got="UNSUPPORTED"
  else
    got=$(printf '%s\n' "$out" | sed -n 's/.*Package: *//p' | head -n1)
  fi
  if [ "$got" = "$expected" ]; then
    ok "$(printf '%-28s -> %s' "$name" "$got")"
  else
    bad "$(printf '%-28s -> %s (expected %s)' "$name" "$got" "$expected")"
    printf '%s\n' "$out" | sed 's/^/        | /'
  fi
}

echo "Distribution detection and package selection:"
check "Ubuntu 24.04"           "$P-ubuntu24.04_amd64.deb" 'ID=ubuntu
ID_LIKE=debian
VERSION_ID="24.04"
VERSION_CODENAME=noble
UBUNTU_CODENAME=noble'
check "Ubuntu 22.04"           "$P-ubuntu22.04_amd64.deb" 'ID=ubuntu
VERSION_ID="22.04"'
check "Ubuntu 24.10 (between)" "$P-ubuntu24.04_amd64.deb" 'ID=ubuntu
VERSION_ID="24.10"'
check "Ubuntu 26.04 (newer)"   "$P-ubuntu24.04_amd64.deb" 'ID=ubuntu
VERSION_ID="26.04"'
check "Ubuntu 20.04 (too old)" "UNSUPPORTED" 'ID=ubuntu
VERSION_ID="20.04"'
check "Linux Mint 22"          "$P-ubuntu24.04_amd64.deb" 'ID=linuxmint
ID_LIKE="ubuntu debian"
VERSION_ID="22"
UBUNTU_CODENAME=noble'
check "Pop!_OS 22.04"          "$P-ubuntu22.04_amd64.deb" 'ID=pop
ID_LIKE="ubuntu debian"
VERSION_ID="22.04"
UBUNTU_CODENAME=jammy'
check "Zorin OS 17"            "$P-ubuntu22.04_amd64.deb" 'ID=zorin
ID_LIKE="ubuntu debian"
VERSION_ID="17"
UBUNTU_CODENAME=jammy'
check "elementary OS 8"        "$P-ubuntu24.04_amd64.deb" 'ID=elementary
ID_LIKE=ubuntu
VERSION_ID="8"
UBUNTU_CODENAME=noble'
check "KDE neon"               "$P-ubuntu24.04_amd64.deb" 'ID=neon
ID_LIKE="ubuntu debian"
VERSION_ID="24.04"
UBUNTU_CODENAME=noble'
check "Debian 12"              "$P-debian12_amd64.deb" 'ID=debian
VERSION_ID="12"
VERSION_CODENAME=bookworm'
check "Debian 13"              "$P-debian13_amd64.deb" 'ID=debian
VERSION_ID="13"
VERSION_CODENAME=trixie'
check "Debian testing (forky)" "$P-debian13_amd64.deb" 'ID=debian
VERSION_CODENAME=forky'
check "Kali Linux Rolling"     "$P-debian13_amd64.deb" 'ID=kali
ID_LIKE=debian
VERSION_ID="2026.2"
VERSION_CODENAME=kali-rolling'
check "Parrot OS 6"            "$P-debian12_amd64.deb" 'ID=parrot
ID_LIKE=debian
VERSION_ID="6.3"
VERSION_CODENAME=lory
DEBIAN_CODENAME=bookworm'
check "MX Linux 23"            "$P-debian12_amd64.deb" 'ID=debian
VERSION_ID="12"
VERSION_CODENAME=bookworm
PRETTY_NAME="MX 23.4 Libretto"'
check "LMDE 6"                 "$P-debian12_amd64.deb" 'ID=linuxmint
ID_LIKE=debian
VERSION_ID="6"
VERSION_CODENAME=bookworm'
check "Fedora 42"              "$P-fedora42.x86_64.rpm" 'ID=fedora
VERSION_ID=42'
check "Fedora 44 (newer)"      "$P-fedora42.x86_64.rpm" 'ID=fedora
VERSION_ID=44'
check "Fedora 40 (too old)"    "UNSUPPORTED" 'ID=fedora
VERSION_ID=40'
check "Nobara 41"              "$P-fedora41.x86_64.rpm" 'ID=nobara
ID_LIKE="rhel centos fedora"
VERSION_ID=41'
check "Arch Linux"             "$P-archlinux-x86_64.pkg.tar.zst" 'ID=arch'
check "Manjaro"                "$P-archlinux-x86_64.pkg.tar.zst" 'ID=manjaro
ID_LIKE=arch'
check "EndeavourOS"            "$P-archlinux-x86_64.pkg.tar.zst" 'ID=endeavouros
ID_LIKE=arch'
check "openSUSE Tumbleweed"    "$P-opensuse-tumbleweed.x86_64.rpm" 'ID=opensuse-tumbleweed
ID_LIKE="opensuse suse"'
check "openSUSE Leap 15.6"     "UNSUPPORTED" 'ID=opensuse-leap
ID_LIKE="suse opensuse"
VERSION_ID="15.6"'
check "Rocky Linux 9"          "UNSUPPORTED" 'ID=rocky
ID_LIKE="rhel centos fedora"
VERSION_ID="9.5"'
check "Unknown distro"         "UNSUPPORTED" 'ID=somethingnew'

echo
echo "Other processors:"
OB_ARCH=aarch64 check "Ubuntu 24.04 on ARM"  "$P-ubuntu24.04_arm64.deb" 'ID=ubuntu
VERSION_ID="24.04"'
OB_ARCH=aarch64 check "Fedora 42 on ARM"     "$P-fedora42.aarch64.rpm" 'ID=fedora
VERSION_ID=42'
OB_ARCH=aarch64 check "Arch on ARM (none)"   "UNSUPPORTED" 'ID=arch'
OB_ARCH=riscv64 check "RISC-V computer"      "UNSUPPORTED" 'ID=ubuntu
VERSION_ID="24.04"'

# check_im <name> <expected input method> <desktop>
check_im() {
  local out got
  printf 'ID=ubuntu\nVERSION_ID="24.04"\n' > "$TMP/os-release"
  out=$(OB_OS_RELEASE="$TMP/os-release" OB_DESKTOP="$3" bash "$INSTALLER" --dry-run --yes 2>&1)
  got=$(printf '%s\n' "$out" | sed -n 's/.*Input method: *\([a-z0-9]*\).*/\1/p' | head -n1)
  if [ "$got" = "$2" ]; then ok "$(printf '%-28s -> %s' "$1" "$got")"
  else bad "$(printf '%-28s -> %s (expected %s)' "$1" "$got" "$2")"; fi
}

echo
echo "Input method choice:"
if pgrep -x ibus-daemon >/dev/null 2>&1 || pgrep -x fcitx5 >/dev/null 2>&1; then
  echo "  (skipped: an input method is running on this computer)"
else
  check_im "GNOME"      ibus   GNOME
  check_im "KDE Plasma" fcitx5 KDE
  check_im "Cinnamon"   ibus   X-Cinnamon
  check_im "XFCE"       fcitx5 XFCE
  check_im "Budgie"     fcitx5 Budgie
fi

echo
echo "Other checks:"
printf 'ID=ubuntu\nVERSION_ID="24.04"\n' > "$TMP/os-release"
if OB_OS_RELEASE="$TMP/os-release" OB_DESKTOP=GNOME bash "$INSTALLER" --dry-run --yes 2>&1 | grep -q -- '--setup-system'; then
  ok "the app sets up the desktop itself"
else
  bad "the app sets up the desktop itself"
fi
if bash "$INSTALLER" --help | grep -q -- '--uninstall'; then ok "--help lists the options"; else bad "--help"; fi
if ! bash "$INSTALLER" --no-such-option >/dev/null 2>&1; then ok "unknown options are rejected"; else bad "unknown options are rejected"; fi

echo
echo "$pass passed, $fail failed"
[ "$fail" = 0 ]
