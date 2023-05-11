cmake_minimum_required(VERSION 3.0)

project(WordFrequencyGame VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "-Wno-error")

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

