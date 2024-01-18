set(NAME "Primitives")

add_library(${NAME} STATIC
        circle.cpp circle.h edge.cpp edge.h polygon.cpp polygon.h shape.cpp shape.h)

target_link_libraries(${NAME} PRIVATE Collisions Common Engine)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_17)