cmake_minimum_required(VERSION 3.20)
project(ImGuiTest)

set(CMAKE_CXX_STANDARD 17)

# 1. Find the packages (vcpkg will handle the paths)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# 2. Define the executable
add_executable(ImGuiTest
    src/main.cpp
    src/App.cpp
    src/UI.cpp
)

target_include_directories(ImGuiTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 3. Link everything together
target_link_libraries(ImGuiTest
    PRIVATE
    imgui::imgui
    glfw        # vcpkg's glfw3 package usually exports the target name 'glfw'
    OpenGL::GL
)