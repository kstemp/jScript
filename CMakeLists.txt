project(jScript)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-std=c++1z")

file(GLOB source "src/*.h" "src/*.cpp")
file (GLOB test-source "test-runner/src/*.cpp" "test-runner/src/*.h")

add_executable("jsc"  ${source})
add_executable("testrunner" ${test-source})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
