project(ImageSequence_tests)


add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/../Include)

add_executable(ImageSequence_tests imageElementTest.cpp)

target_link_libraries(ImageSequence_tests gtest gtest_main ImageSequence)

add_test(
        NAME ImageSequence_tests
        COMMAND ImageSequence_tests
)
