#!/bin/bash


install_debian() {
  sudo apt update
  sudo apt-get install -y libgl1-mesa-dev libx11-dev
}

install_redhat() {
  sudo dnf install -y mesa-libGL-devel libX11-devel
}


if [ -f /etc/debian_version ]; then
  echo "Debian/Ubuntu OS detected."
  install_debian
elif [ -f /etc/redhat-release ]; then
  echo "Redhat OS detected."
  install_redhat
else
  echo "OS not supported, go to get a real OS."
  exit 1
fi

echo "Needed dependencies has been installed"
