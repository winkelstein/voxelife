cmake_minimum_required(VERSION 3.14)
project(ObscureEngine
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(OBSCUREENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/json/single_include)

file(GLOB
        SOURCE_FILES "src/*.cpp")

add_library(ObscureEngine SHARED ${SOURCE_FILES})