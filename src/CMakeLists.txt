add_subdirectory(libImageSequence)

if(${IMAGE_SEQUENCE_BUILD_PYTHON})
    add_subdirectory(python)
endif()