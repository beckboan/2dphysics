set(NAME "App")

add_executable(${NAME} main.cpp)
install(TARGETS ${NAME} RUNTIME DESTINATION .)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${NAME} PRIVATE cxx_std_17)

target_link_libraries(${NAME}
        PUBLIC SDL2::SDL2 imgui PRIVATE Collisions Common Engine Primitives)
