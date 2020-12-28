cmake_minimum_required(VERSION 3.16)
project(ImageSequence
        VERSION 0.1.0
        LANGUAGES CXX
        )


set(ImageSequence_VERSION "${CMAKE_PROJECT_VERSION}-dev.1")
set(CMAKE_CXX_STANDARD 14)

# Build type
if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "Setting build type to 'Release' as none was set.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type." FORCE)
endif()

# options
option(IMAGE_SEQUENCE_BUILD_PYTHON "Build python module" ON)
option(IMAGE_SEQUENCE_BUILD_TEST "Build unit tests" OFF)


enable_testing()

add_subdirectory(src)

# Build unit tests.
if(${IMAGE_SEQUENCE_BUILD_TEST})
    add_subdirectory(tests)
endif()
