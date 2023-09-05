cmake_minimum_required(VERSION 3.14)
project(biolife
        VERSION 0.1.0
        LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
        
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(src/ObscureEngine/include)

SET(SOURCE_FILES
        src/main.cpp
)

SET(OBSCURE_SOURCE_FILES
        src/ObscureEngine/src/FPSCounter.cpp
        src/ObscureEngine/src/Window.cpp
        src/ObscureEngine/src/Shader.cpp
        src/ObscureEngine/src/Screen.cpp
        src/ObscureEngine/src/Camera.cpp
        src/ObscureEngine/src/Mesh.cpp
        src/ObscureEngine/src/Model.cpp
        src/ObscureEngine/src/EngineApp.cpp
        src/ObscureEngine/src/Logger.cpp
        src/ObscureEngine/src/ShaderImporter.cpp
        )

add_library(obscureengine SHARED ${OBSCURE_SOURCE_FILES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} OpenGL GLEW::GLEW glfw obscureengine)