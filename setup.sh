#!/bin/bash

# Download SFML 2.4.2 and TinyXML2 4.0.1 (the ugly way)

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

for package in ${urls[@]}; do
	name=${package##*/}
	echo -n "Downloading $name..."
	wget -q $package
	if [ $? -eq 0 ]; then
		echo "OK"
	else
		echo "fail"
		return 1
	fi
	dpkg -x $name .
	rm -f $name
done
mv usr/* .
rmdir usr

echo ""

# Install TMXparser

git clone https://github.com/sainteos/tmxparser.git || exit 1
cd tmxparser
mkdir build && cd build
cmake -D CMAKE_PREFIX_PATH=../../ -D CMAKE_INSTALL_PREFIX=../../ -D CMAKE_CXX_COMPILER=$(which g++) -D CMAKE_C_COMPILER=$(which gcc) ..
make install || exit 1
cd ../../
rm -rf tmxparser
