cmake_minimum_required(VERSION 3.14)
project(ObscureEngine
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wno-unused-variable -Wno-unused-parameter")

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/glew)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/bullet3)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/glfw)

set(OBSCUREENGINE_LIBRARIES
                                OpenGL
                                GLEW::GLEW
                                glfw
                                ${BULLET_LIBRARIES}
)

set(OBSCUREENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${BULLET_INCLUDE_DIRS})

file(GLOB
        SOURCE_FILES "src/*.cpp")

add_library(ObscureEngine SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
                                        PUBLIC
                                        ${CMAKE_CURRENT_SOURCE_DIR}/include
                                        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/json/single_include
                                        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glm)

target_link_libraries(${PROJECT_NAME} ${OBSCUREENGINE_LIBRARIES})