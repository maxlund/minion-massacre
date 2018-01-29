cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)
project(TDDI22_Projekt)
set (CMAKE_CXX_STANDARD 14)

if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/6.1.0.*"))
    set(CMAKE_CXX_COMPILER /sw/gcc-6.1.0/bin/g++)
endif()

include_directories(include)
link_directories(lib)
link_directories(lib/x86_64-linux-gnu)

add_custom_command(
        OUTPUT
        ${CMAKE_SOURCE_DIR}/lib/x86_64-linux-gnu/libsfml-system.so
        ${CMAKE_SOURCE_DIR}/lib/x86_64-linux-gnu/libtinyxml2.so
        ${CMAKE_SOURCE_DIR}/lib/libtmxparser.so
        ${CMAKE_SOURCE_DIR}/include/SFML/System.hpp
        ${CMAKE_SOURCE_DIR}/include/tinyxml2.h
        ${CMAKE_SOURCE_DIR}/include/tmxparser/Tmx.h
)

add_executable(main
        lib/x86_64-linux-gnu/libsfml-system.so
        lib/x86_64-linux-gnu/libtinyxml2.so
        lib/libtmxparser.so
        include/SFML/System.hpp
        include/tinyxml2.h
        include/tmxparser/Tmx.h

        src/main.cpp
        src/Level.cpp
        src/ResourceManager.cpp
        src/Movable.cpp
        src/Minion.cpp
        src/Minion.h
        src/Entity.cpp
        src/Tower.cpp
        src/Tower.h
        src/Collidable.cpp
        src/Collidable.h
        src/Projectile.cpp
        src/Projectile.h
        src/Game.cpp
        src/Game.h
        src/Button.cpp
        src/ArrowTower.cpp
        src/ArrowTower.h
        src/FlameTower.cpp
        src/FlameTower.h
        src/BulletTower.cpp
        src/BulletTower.h
        src/BombTower.cpp
        src/BombTower.h
        src/Bomb.cpp
        src/Bomb.h
        src/Obstacle.cpp
        src/Obstacle.h
        src/SpikeObstacle.cpp
        src/SpikeObstacle.h
        src/Effect.cpp
        src/Effect.h
        src/FreezeEffect.cpp
        src/FreezeEffect.h
        src/FreezeObstacle.cpp
        src/FreezeObstacle.h
        src/PoisonEffect.h
        src/PoisonEffect.cpp
        src/PoisonObstacle.h
        src/PoisonObstacle.cpp
        src/AreaTower.cpp
        src/AreaTower.h)
target_link_libraries(main sfml-system sfml-window sfml-graphics tinyxml2 tmxparser)
