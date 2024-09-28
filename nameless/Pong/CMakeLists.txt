cmake_minimum_required(VERSION 3.28)
project(pong)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

find_package(raylib REQUIRED)

set (SOURCES
     src/main.c
)

add_executable(pong  ${SOURCES})
target_link_libraries(pong raylib)
