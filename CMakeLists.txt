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


add_subdirectory(src/third-party/bullet3)
add_subdirectory(src/ObscureEngine)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/ObscureEngine/include)
include_directories(${BULLET_INCLUDE_DIRS})

file(GLOB
        SOURCE_FILES "src/*.cpp")

set(LIBRARIES
                OpenGL
                GLEW::GLEW
                glfw
                ObscureEngine
                ${BULLET_LIBRARIES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})