cmake_minimum_required(VERSION 3.20)
project(LomusEngineCmake)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Thirdparty/glad)
add_subdirectory(Thirdparty/glfw)
add_subdirectory(Thirdparty/glm)
add_subdirectory(Thirdparty/stb)
add_subdirectory(Thirdparty/reactPhysics3d)

file(GLOB_RECURSE LOMUS_ENGINES_SOURCE Lomus/*.hpp Lomus/*.cpp Lomus/*.h Lomus/*.c Lomus/Physics/*.cpp Lomus/Physics/DebugVBO.cpp Lomus/Physics/DebugVAO.cpp Lomus/Physics/DebugVAO.h Lomus/Physics/DebugVBO.h Lomus/Physics/DebugRenderer.cpp Lomus/Physics/DebugRenderer.h Lomus/Physics/*.h Lomus/Utils/*.cpp Lomus/Utils/*.h Thirdparty/imgui/*.h Thirdparty/imgui/*.cpp)
add_executable(LomusEngineCmake ${LOMUS_ENGINES_SOURCE} Main.cpp  )


target_link_libraries(LomusEngineCmake PUBLIC glad)
target_link_libraries(LomusEngineCmake PUBLIC glfw)
target_link_libraries(LomusEngineCmake PUBLIC glm::glm)
target_link_libraries(LomusEngineCmake PUBLIC stb)
target_link_libraries(LomusEngineCmake PUBLIC reactphysics3d)


target_include_directories(LomusEngineCmake PUBLIC Thirdparty/json/include)