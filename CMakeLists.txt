cmake_minimum_required(VERSION 3.0.0)
project(2dphysics VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()



set(SOURCES
    src/vec2d.cpp
    src/main.cpp
    src/physicsworld.cpp
    src/physicsobject.cpp
)

add_executable(2dphysics ${SOURCES})

target_include_directories(2dphysics
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include()
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
