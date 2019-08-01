project(jScript)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pthread")

file(GLOB source "src/*.h" "src/*.cpp")
file (GLOB test-source "test-runner/src/*.cpp" "test-runner/src/*.h")

add_executable(jsc  ${source})

set_target_properties(jsc
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "bin/"
)

add_executable(testrunner ${test-source})

set_target_properties(testrunner
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "test-runner/bin/"
)

target_link_libraries(testrunner curlpp)
target_link_libraries(testrunner curl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
