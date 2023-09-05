cmake_minimum_required(VERSION 3.14)
project(biolife
        VERSION 0.1.0
        LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
        
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
        
SET(SOURCE_FILES
        src/main.cpp
        src/Engine/FPSCounter.cpp
        src/Engine/WS/Window.cpp
        src/Engine/GLTK/Shader.cpp
        src/Engine/Screen.cpp
        src/Engine/Camera.cpp
        src/Engine/Mesh.cpp
        src/Engine/Model.cpp
        src/Engine/EngineApp.cpp
        src/Engine/Logger.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} OpenGL GLEW::GLEW glfw)