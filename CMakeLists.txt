cmake_minimum_required(VERSION 3.14)
project(biolife
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -D _RELEASE -O2")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(src/ObscureEngine/include)

file(GLOB
        SOURCE_FILES "src/*.cpp")
file(GLOB
        OBSCURE_SOURCE_FILES "src/ObscureEngine/src/*.cpp")

add_library(obscureengine SHARED ${OBSCURE_SOURCE_FILES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} OpenGL GLEW::GLEW glfw obscureengine)
