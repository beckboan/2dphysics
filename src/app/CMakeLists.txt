set(NAME "app")

add_executable(${NAME} main.cpp)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${NAME} PRIVATE cxx_std_17)

target_link_libraries(${NAME} core)

if (WIN32)
# Copy SDL2.dll to the output directory
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:app>)
endif()
