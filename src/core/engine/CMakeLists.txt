set(NAME "Engine")

add_library(${NAME} STATIC
        engine.cpp engine.h runtimedata.cpp runtimedata.h scene.cpp scene.h world.cpp world.h)

target_link_libraries(${NAME} PRIVATE Collisions Common Primitives)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_17)