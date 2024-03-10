set(NAME "engine")

add_library(${NAME} STATIC
        runtimedata.cpp runtimedata.h world.cpp world.h
        engine.cpp)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${NAME} PUBLIC yaml-cpp::yaml-cpp PRIVATE core)
target_compile_features(${NAME} PRIVATE cxx_std_17)