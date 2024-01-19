set(NAME "collisions")

add_library(${NAME} STATIC
        collisions.cpp collisions.h rigidbody.cpp rigidbody.h AABB.cpp AABB.h)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${NAME} PRIVATE core)
target_compile_features(${NAME} PRIVATE cxx_std_17)