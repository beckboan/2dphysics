message(STATUS "Fetching imgui file dialog ...")

set(CMAKE_CXX_STANDARD 20)

FetchContent_GetProperties(imguifiledialog)
if(NOT imguifiledialog_POPULATED)
  FetchContent_Populate(imguifiledialog)
endif()

message(STATUS "ImGuiFileDialog Src Dir: ${imguifiledialog_SOURCE_DIR}")

add_library(
        imguifiledialog
        ${imguifiledialog_SOURCE_DIR}/ImGuiFileDialog.cpp
        ${imguifiledialog_SOURCE_DIR}/ImGuiFileDialog.h

)

target_include_directories(imguifiledialog PUBLIC ${imguifiledialog_SOURCE_DIR})
target_link_libraries(imguifiledialog PUBLIC imgui)

FetchContent_MakeAvailable(imguifiledialog)
