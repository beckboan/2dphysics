set(NAME "gui")

add_library(${NAME} STATIC
        window.cpp
        window.h
        application.cpp
        application.h)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${NAME} PUBLIC SDL2::SDL2 imgui PRIVATE core)
target_compile_features(${NAME} PRIVATE cxx_std_17)