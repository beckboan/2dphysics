cmake_minimum_required(VERSION 3.28.0)
project(2dphysics VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES
    src/mathfuncs.cpp
    src/main.cpp
    src/world.cpp
    src/shape.cpp
    src/rigidbody.cpp
    src/collisions.cpp
    src/circle.cpp
    src/polygon.cpp 
    src/scene.cpp
    src/AABB.cpp
    src/engine.cpp
    src/runtimedata.cpp
)

add_executable(2dphysics ${SOURCES})

target_include_directories(2dphysics PRIVATE ${PROJECT_SOURCE_DIR}/include())
#target_include_directories(2dphysics PRIVATE ${PROJECT_SOURCE_DIR}/tests())
target_include_directories(2dphysics PUBLIC $(SDL2_INCLUDE_DIR))
target_include_directories(2dphysics PUBLIC $(OPENGL_INCLUDE_DIR))

target_link_libraries(2dphysics SDL2::SDL2)
target_link_libraries(2dphysics OpenGL::GL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
