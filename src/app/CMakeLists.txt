set(NAME "app")

add_executable(${NAME} main.cpp)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${NAME} PRIVATE cxx_std_17)

target_link_libraries(${NAME} core)
