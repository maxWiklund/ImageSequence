find_package(Boost 1.4 REQUIRED COMPONENTS regex filesystem)

set(SOURCES
        imageElement.cpp
        scanDir.cpp
        )

set(IMAGESSEQUENCE_INCLUDE ${PROJECT_SOURCE_DIR}/Include)
include_directories(${IMAGESSEQUENCE_INCLUDE})


add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} Boost::regex Boost::filesystem)


if(IMAGE_SEQUENCE_BUILD_PYTHON AND UNIX)
    # The Python bindings is a 'module' which is a dynamic library on Linux
    # (i.e. '-fPIC' needed), but a static library on Windows.

    # If supported for the target machine, emit position-independent code
    # suitable for dynamic linking.
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()
