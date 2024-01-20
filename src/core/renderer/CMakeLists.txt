set(NAME "renderer")

add_library(${NAME} STATIC
        scene.cpp scene.h)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${NAME} PRIVATE core)
target_compile_features(${NAME} PRIVATE cxx_std_17)