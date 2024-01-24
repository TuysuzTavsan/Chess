cmake_minimum_required(VERSION 3.22)

project(chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess
Src/drawable2D.cpp
Src/apl.cpp
Src/main.cpp
Src/rectangle.cpp
Src/shader.cpp
Src/text.cpp
Src/texture.cpp
Dependencies/Include/glad.c
Headers/ecs/ComponentManager.cpp
Headers/ecs/ECSManager.cpp
Headers/ecs/EntityManager.cpp
GameCode/Chess/

)

target_include_directories(chess PRIVATE
Dependencies/Include
Dependencies/Include/freetype2
Headers
Headers/Types
Headers/ECS
GameCode/
)

target_link_libraries(chess
GL
glfw
freetype)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
set(CMAKE_BUILD_TYPE "Debug")
