cmake_minimum_required(VERSION 3.14)
project(PacmanSFML)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCE_FILES
        src/main.cpp src/Game.cpp src/Game.h src/ResourceHandler.cpp src/ResourceHandler.h
        src/tmxsrc/FreeFuncs.cpp
        src/tmxsrc/ImageLayer.cpp
        src/tmxsrc/LayerGroup.cpp
        src/tmxsrc/Map.cpp
        src/tmxsrc/meson.build
        src/tmxsrc/miniz.c
        src/tmxsrc/miniz.h
        src/tmxsrc/Object.cpp
        src/tmxsrc/ObjectGroup.cpp
        src/tmxsrc/ObjectTypes.cpp
        src/tmxsrc/Property.cpp
        src/tmxsrc/TileLayer.cpp
        src/tmxsrc/Tileset.cpp
        src/tmxsrc/detail/pugixml.cpp
        src/Player.cpp src/Player.h src/Enemy.cpp src/Enemy.h src/Coin.cpp src/Coin.h src/Menus/MainMenu.cpp src/Menus/MainMenu.h src/Menus/GameOverMenu.cpp src/Menus/GameOverMenu.h)

add_executable(PacmanSFML ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(CMAKE_PREFIX_PATH C:/)

target_link_libraries (PacmanSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)