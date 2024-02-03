set(NAME "Vendor")

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG v1.90.1-docking
)
add_subdirectory(imgui)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
        GIT_TAG release-2.26.3
)
add_subdirectory(sdl)
