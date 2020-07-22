cmake_minimum_required(VERSION 3.16)
project(ImageSequence VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.4 REQUIRED COMPONENTS regex)


add_subdirectory(src/libImageSequence)


