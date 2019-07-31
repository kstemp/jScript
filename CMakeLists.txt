project(jScript)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-std=c++1z")

file(GLOB source "src/*.h" "src/*.cpp")


add_executable(jsc  ${source})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
