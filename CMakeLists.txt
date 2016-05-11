cmake_minimum_required(VERSION 3.5)
project(SnailColony)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/Compile)
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
    src/Tile.cpp src/SnailColony.cpp headers/SnailColony.h)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})
add_executable(SnailColony ${SOURCE_FILES})
target_link_libraries(SnailColony ${CURSES_LIBRARIES})