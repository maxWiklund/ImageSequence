# Build python module.

find_package(Python REQUIRED COMPONENTS Interpreter Development)


set(SOURCES
        pyModule.cpp
        )

include_directories(${PROJECT_SOURCE_DIR}/Include)

# Create python module.
add_library(PyImageSequence SHARED ${SOURCES})


target_link_libraries(PyImageSequence
        PRIVATE
        ImageSequence
        )

set_target_properties(PyImageSequence PROPERTIES
        # Remove lib prefix.
        PREFIX ""
        )

if(WIN32)
    # Windows uses .pyd extension for python modules.
    set_target_properties(PyImageSequence PROPERTIES
            SUFFIX ".pyd"
            )
endif()

target_include_directories(PyImageSequence
        PRIVATE
        ${pybind11_INCLUDE_DIR}

        SYSTEM
        ${Python_INCLUDE_DIRS}
        )


if(WIN32)
    set(PYTHON_INSTALL_LIB_PATH "lib${LIB_SUFFIX}/site-packages")
else()
    set(PYTHON_INSTALL_LIB_PATH "lib${LIB_SUFFIX}/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages")
endif()

message(STATUS "Python install paths is: " ${PYTHON_INSTALL_LIB_PATH})
install(TARGETS PyImageSequence
        LIBRARY DESTINATION ${PYTHON_INSTALL_LIB_PATH}
        )
