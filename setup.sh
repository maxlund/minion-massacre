#!/bin/bash

# Download SFML 2.4.2 and TinyXML2 4.0.1 (the ugly way)

pm=""
pkgs=""

check_distro()
{
    local which=$(cat /etc/issue | sed -e 's/\s\+/ /g' -e 's/^\s\+//g')
    which=${which,,}
    case $which in
        *arch*)
            echo "ARCH detected!"
            pm="pacman -S"
            pkgs="sfml tinyxml2 libjpeg6-turbo"
            ;;
        *mint*|*ubuntu*)
            echo "DEBIAN detected!"
            pm="apt install -y"
            pkgs="libsfml-dev libsfml-doc \
                libsfml-audio2.3v5 libsfml-graphics2.3v5 \
                libsfml-network2.3v5 libsfml-system2.3v5 \
                libsfml-window2.3v5 libtinyxml2-dev \
                libjpeg62-dev"
            ;;
        *fedora*|*rhel*|*redhat*)
            echo "RHEL / CentOS / Fedora detected!"
            pm="yum install"
            pkgs="sfml2-devel tinyxml2-devel libjpeg62"
            ;;
        *poky*)
            echo "Yocto (Poky) detected!"
            pm="opkg"
            ;;
        *)
            echo "Wrong distro. GTFO" 2<&1
            exit 1
    esac
}

# Check distro, and update pm
check_distro

echo "Getting needed pkgs ..."
sudo $pm $pkgs
if [ $? -eq 0 ]; then
    echo "[ok]"
else
    echo "[fail]"
    exit 1
fi


echo ""

# Install TMXparser

test -d tmxparser || git clone https://github.com/sainteos/tmxparser.git || exit 1
cd tmxparser
test -d build || mkdir build
cd build
cmake -D CMAKE_PREFIX_PATH=../../ -D CMAKE_INSTALL_PREFIX=../../ -D CMAKE_CXX_COMPILER=$(which g++) -D CMAKE_C_COMPILER=$(which gcc) ..
make install -j8 || exit 1
cd ../../
test -d build || mkdir build
cd build
cmake ..
make -j8

