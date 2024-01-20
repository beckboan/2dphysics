set(NAME "engine")

add_library(${NAME} STATIC
        engine.cpp engine.h runtimedata.cpp runtimedata.h world.cpp world.h)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${NAME} PUBLIC SDL2::SDL2 imgui PRIVATE core)
target_compile_features(${NAME} PRIVATE cxx_std_17)