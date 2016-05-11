cmake_minimum_required(VERSION 3.3)
project(SnailColony)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES
    headers/CommonUtils.h
    headers/includes.h
    headers/Map.h
    headers/Snail.h
    headers/StatusBar.h
    headers/Tile.h
    src/CommonUtils.cpp
    src/main.cpp
    src/Map.cpp
    src/Snail.cpp
    src/StatusBar.cpp
    src/Tile.cpp)

add_executable(SnailColony ${SOURCE_FILES})
target_link_libraries(SnailColony ${CURSES_LIBRARIES})