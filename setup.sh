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
                libsfml-audio2 libsfml-graphics2 \
                libsfml-network2 libsfml-system2 \
                libsfml-windows2 libtinyxml2-dev \
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

urls=(
	http://ftp.se.debian.org/debian/pool/main/libj/libjpeg-turbo/libjpeg62-turbo_1.3.1-12_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/libs/libsfml/libsfml-dev_2.4.2+dfsg-1_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/libs/libsfml/libsfml-audio2.4_2.4.2+dfsg-1_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/libs/libsfml/libsfml-graphics2.4_2.4.2+dfsg-1_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/libs/libsfml/libsfml-network2.4_2.4.2+dfsg-1_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/libs/libsfml/libsfml-system2.4_2.4.2+dfsg-1_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/libs/libsfml/libsfml-window2.4_2.4.2+dfsg-1_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/t/tinyxml2/libtinyxml2-dev_4.0.1-1_amd64.deb
	http://ftp.se.debian.org/debian/pool/main/t/tinyxml2/libtinyxml2-4_4.0.1-1_amd64.deb
)

# Check distro, and update pm
check_distro

#for package in ${urls[@]}; do
#	echo -n "Downloading $name..."
#	wget -q $package
#	if [ $? -eq 0 ]; then
#		echo "OK"
#	else
#		echo "fail"
#		return 1
#	fi
#	dpkg -x $name .
#	rm -f $name
#done
#mv usr/* .
#rmdir usr

echo "Getting needed pkgs ..."
#sudo `$pm $pkgs` &> /dev/null
`sudo $pm $pkgs`
if [ $? -eq 0 ]; then
    echo "[ok]"
else
    echo "[fail]"
    exit 1
fi


echo ""

# Install TMXparser

git clone https://github.com/sainteos/tmxparser.git || exit 1
cd tmxparser
mkdir build && cd build
cmake -D CMAKE_PREFIX_PATH=../../ -D CMAKE_INSTALL_PREFIX=../../ -D CMAKE_CXX_COMPILER=$(which g++) -D CMAKE_C_COMPILER=$(which gcc) ..
make install || exit 1
cd ../../
rm -rf tmxparser
