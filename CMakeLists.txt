cmake_minimum_required(VERSION 3.20)
project(LomusEngineCmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")


add_subdirectory("Thirdparty/glad")
add_subdirectory(Thirdparty/glfw)
add_subdirectory(Thirdparty/glm)
add_subdirectory(Thirdparty/stb)
add_subdirectory(Thirdparty/reactPhysics3d)
add_subdirectory(Thirdparty/assimp)
add_subdirectory(Thirdparty/visualNodeSystem)
add_subdirectory(Thirdparty/spdlog)
add_subdirectory(Thirdparty/yaml-cpp-0.8.0)

file(GLOB_RECURSE LOMUS_ENGINES_SOURCE Lomus/*.hpp Lomus/*.cpp Lomus/*.h Lomus/Renderer/Billboard.h Lomus/Renderer/Billboard.cpp Lomus/*.c Lomus/Physics/*.cpp Lomus/Physics/DebugVBO.cpp Lomus/Physics/DebugVAO.cpp Lomus/Physics/DebugVAO.h Lomus/Physics/DebugVBO.h Lomus/Physics/DebugRenderer.cpp Lomus/Physics/DebugRenderer.h Lomus/Physics/*.h Lomus/Utils/*.cpp Lomus/Utils/*.h Thirdparty/imgui/*.h Thirdparty/imgui/*.cpp )
add_executable(LomusEngineCmake ${LOMUS_ENGINES_SOURCE} Main.cpp
        Thirdparty/ImGuiColorTextEdit/TextEditor.cpp
        Thirdparty/ImGuiColorTextEdit/TextEditor.h
        Thirdparty/imgui/ImGuiFileBrowser.h
        Thirdparty/imgui/ImGuiFileBrowser.cpp
        Lomus/Utils/Toolbox.cpp
        Lomus/Utils/Toolbox.cpp
        Lomus/Lights/Shadows/Shadows.hpp
        Lomus/Renderer/Atomus.hpp
        Lomus/Core/ProjectManager.cpp
        Lomus/Core/ProjectManager.h
        Lomus/Editor/Launcher.h
        Lomus/Core/Window.cpp
        Lomus/Core/Window.h
)

include_directories(
        Thirdparty/assimp/include
)

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
)
foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()


target_link_libraries(LomusEngineCmake PUBLIC glad)
target_link_libraries(LomusEngineCmake PUBLIC glfw)
target_link_libraries(LomusEngineCmake PUBLIC glm::glm)
target_link_libraries(LomusEngineCmake PUBLIC stb)
target_link_libraries(LomusEngineCmake PUBLIC reactphysics3d)
target_link_libraries(LomusEngineCmake PUBLIC assimp)
target_link_libraries(LomusEngineCmake PUBLIC VisualNodeSystem)
target_link_libraries(LomusEngineCmake PUBLIC spdlog)
target_link_libraries(LomusEngineCmake PUBLIC yaml-cpp)

target_include_directories(LomusEngineCmake PUBLIC Thirdparty/json/include)
target_include_directories(LomusEngineCmake PUBLIC Thirdparty/ImGuiColorTextEdit)