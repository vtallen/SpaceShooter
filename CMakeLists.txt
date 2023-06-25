cmake_minimum_required(VERSION 3.14)
project(SwaglordsOfSpace)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES main.cpp game.cpp game.h player.h player.cpp bullet.h bullet.cpp)
add_executable(SwaglordsOfSpace ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SwaglordsOfSpace sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
