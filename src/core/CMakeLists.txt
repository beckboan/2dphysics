set(CORE_MODULES
        engine
        primitives
        dynamics
        rendering
        common
        gui
)

set(NAME "core")

foreach (module ${CORE_MODULES})
    add_subdirectory(${module})
endforeach ()

add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

foreach (module ${CORE_MODULES})
    target_link_libraries(${NAME} INTERFACE ${module})
endforeach ()

