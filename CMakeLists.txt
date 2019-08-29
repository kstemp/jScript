project(jScript)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pthread")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# jsc (jScript interpreter) configuration

file(GLOB source "src/*.h" "src/*.cpp")

add_executable(jsc  ${source})

set_target_properties(jsc
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "bin/"
)
