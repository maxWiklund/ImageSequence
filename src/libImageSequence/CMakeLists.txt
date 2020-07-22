
set(LIB_IMAGE_SEQUENCE_SRC
        image_element.cpp
        )

include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/Include)
add_library(ImageSequence SHARED ${LIB_IMAGE_SEQUENCE_SRC})

target_link_libraries(${PROJECT_NAME} Boost::regex)
