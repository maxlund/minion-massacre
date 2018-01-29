# Minion Massacre


## Installation

* Dependencies:
    * SFML 2.4
    * TinyXML2
    * TMXparser
    
All dependencies can be downloaded by running `./setup.sh`.

To install & run:
```
./setup.sh
cd build
./main
```

Alternative version if the version of GCC pointed to by $PATH is not detected:
```
mkdir build && cd build
cmake -D CMAKE_C_COMPILER=$(which gcc) -DCMAKE_CXX_COMPILER=$(which g++) ..
make
```
