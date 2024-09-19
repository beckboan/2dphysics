set(NAME "Vendor")

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
  GIT_TAG v1.90.6-docking)
add_subdirectory(imgui)

FetchContent_Declare(
  SDL2
  GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
  GIT_TAG release-2.30.3)
add_subdirectory(sdl)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp.git"
  GIT_TAG yaml-cpp-0.7.0)
add_subdirectory(yaml-cpp)

FetchContent_Declare(
  imguifiledialog
  GIT_REPOSITORY "https://github.com/aiekick/ImGuiFileDialog.git"
  GIT_TAG v0.6.7)
add_subdirectory(imguifiledialog)
