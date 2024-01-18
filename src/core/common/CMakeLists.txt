set(NAME "Common")

add_library(${NAME} STATIC
        common.h mathfuncs.cpp mathfuncs.h)

target_link_libraries(${NAME} PRIVATE Collisions Engine Primitives)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_17)