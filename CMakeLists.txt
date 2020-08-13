cmake_minimum_required(VERSION 3.16)
project(ImageSequence
        VERSION 0.1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 14)

option(IMAGE_SEQUENCE_BUILD_PYTHON "Build python module" ON)
option(IMAGE_SEQUENCE_BUILD_TEST "Build unit tests" OFF)


enable_testing()

add_subdirectory(src)

# Build unit tests.
if(${IMAGE_SEQUENCE_BUILD_TEST})
    add_subdirectory(tests)
endif()
