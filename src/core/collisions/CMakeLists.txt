set(NAME "Collisions")

add_library(${NAME} STATIC
        collisions.cpp collisions.h rigidbody.cpp rigidbody.h AABB.cpp AABB.h)

target_link_libraries(${NAME} PRIVATE Common Engine Primitives)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${NAME} PRIVATE cxx_std_17)