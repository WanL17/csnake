#!/bin/bash

set -e

echo "*Installation of gcc and ncurses*"

# Vérification des privilèges
if [[ $EUID -ne 0 ]]; then
  echo "Execute this script with sudo."
  exit 1
fi

# Chargement des informations de la distribution
if [[ -f /etc/os-release ]]; then
  source /etc/os-release
else
  echo "Unknown distro."
  exit 1
fi

install_debian() {
  apt update
  apt install -y \
    build-essential \
    gcc \
    g++ \
    make \
    libncurses-dev \
    libncursesw5-dev
}

install_arch() {
  pacman -Sy --noconfirm \
    base-devel \
    gcc \
    ncurses
}

install_fedora() {
  dnf install -y \
    gcc \
    gcc-c++ \
    make \
    ncurses-devel
}

install_rhel() {
  if command -v dnf >/dev/null 2>&1; then
    dnf install -y \
      gcc \
      gcc-c++ \
      make \
      ncurses-devel
  else
    yum install -y \
      gcc \
      gcc-c++ \
      make \
      ncurses-devel
  fi
}

install_opensuse() {
  zypper --non-interactive install \
    gcc \
    gcc-c++ \
    make \
    ncurses-devel
}

echo "Your distro : $PRETTY_NAME"

case "$ID" in
ubuntu | debian | linuxmint | pop | elementary | kali)
  install_debian
  ;;
arch | manjaro | endeavouros)
  install_arch
  ;;
fedora)
  install_fedora
  ;;
rhel | rocky | almalinux | centos)
  install_rhel
  ;;
opensuse* | sles)
  install_opensuse
  ;;
*)
  echo "Distro not available : $ID"
  exit 1
  ;;
esac

echo "Install finished."
echo

if command -v gcc >/dev/null 2>&1; then
  echo "gcc version :"
  gcc --version | head -n 1
else
  echo "WARNING: gcc not found after install !"
fi
