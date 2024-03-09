cmake_minimum_required(VERSION 3.27.0)

project(
        2dphysics
        DESCRIPTION "Simple 2D Physics Engine"
        VERSION 0.1.0
        LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS
        ON
        CACHE INTERNAL "")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor)
add_subdirectory(src)
