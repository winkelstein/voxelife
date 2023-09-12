cmake_minimum_required(VERSION 3.14)
project(biolife
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/ObscureEngine)

file(GLOB
        SOURCE_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ObscureEngine)