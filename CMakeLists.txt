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

#find_package(SDL2 REQUIRED)
#find_package(OpenGL REQUIRED)
#
#set(SOURCES
#        src/core/common/mathfuncs.cpp
#        src/app/main.cpp
#        src/core/engine/world.cpp
#        src/core/primitives/shape.cpp
#        src/core/dynamics/rigidbody.cpp
#        src/core/dynamics/dynamics.cpp
#        src/core/primitives/circle.cpp
#        src/core/primitives/polygon.cpp
#        src/core/engine/scene.cpp
#        src/core/dynamics/AABB.cpp
#        src/core/engine/engine.cpp
#        src/core/engine/runtimedata.cpp
#        src/core/primitives/edge.cpp)
#
#add_executable(2dphysics ${SOURCES})
#
#target_include_directories(2dphysics PRIVATE ${PROJECT_SOURCE_DIR}/include ())
## target_include_directories(2dphysics PRIVATE ${PROJECT_SOURCE_DIR}/tests())
#target_include_directories(2dphysics PUBLIC $(SDL2_INCLUDE_DIR))
#target_include_directories(2dphysics PUBLIC $(OPENGL_INCLUDE_DIR))
##target_link_libraries(2dphysics OpenGL::GL)
