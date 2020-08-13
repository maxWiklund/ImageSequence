#include "libImageSequence/imageElement.hpp"
#include <libImageSequence/scanDir.hpp>

#include <gtest/gtest.h>


TEST(imageElement, test_fined_frame) {
    std::string test_path = "/mock/path.9999.ext";
    ImageElement mock_element{test_path};

    std::vector<int> expected_value = {9999};
    EXPECT_EQ(expected_value, mock_element.getFrames());
}


TEST(imageElement, test_not_fined_frame) {
    std::string test_path = "/mock/abc_v53.exr";
    ImageElement mock_element{test_path};
    std::vector<int> expected_value = {};

    EXPECT_EQ(expected_value, mock_element.getFrames());
    EXPECT_EQ("/mock/abc_v53.exr", mock_element.getFilePath());
}


TEST(imageElement, test_remove_frame_from_path){
    std::string test_path = "/mock/m9999path.9999.ext";
    ImageElement mock_element{test_path};

    EXPECT_EQ("/mock/m9999path.%04d.ext", mock_element.getFilePath());
}


TEST(imageElement, test_eval_frame_at){
    std::string test_path = "/mock/char_cat_DIFFUSE_v73.1100.exr";
    ImageElement mock_element{test_path};

    EXPECT_EQ("/mock/char_cat_DIFFUSE_v73.0003.exr", mock_element.evalAtFrame(3));
}


TEST(imageElement, test_dirname){
    std::string test_path = "/mock/char_cat_DIFFUSE_v73.1100.exr";
    ImageElement mock_element{test_path};

    EXPECT_EQ("/mock", mock_element.dirname());
}


TEST(imageElement, test_basename){
    std::string test_path = "/mock/char_cat_DIFFUSE_v73.1001.exr";
    ImageElement mock_element{test_path};

    EXPECT_EQ("char_cat_DIFFUSE_v73.%04d.exr", mock_element.basename());
}


TEST(imageElement, test_basename_alredy_formatted){
    std::string test_path = "/mock/char_cat_DIFFUSE_v73.%04d.exr";
    ImageElement mock_element{test_path};

    EXPECT_EQ("char_cat_DIFFUSE_v73.%04d.exr", mock_element.basename());
}


TEST(imageElement, test_change_name){
    ImageElement mock_element{"/mock/name12342.1001.exr"};
    mock_element.name = "mock";
    EXPECT_EQ("mock.%04d.exr", mock_element.basename());
}


TEST(imageElement, test_change_extension){
    ImageElement mock_element{"/mock/abc.exr"};
    mock_element.extension = ".tx";
    EXPECT_EQ("abc.tx", mock_element.basename());
}


TEST(imageElement, test_getPaths){
    std::string test_path = "/mock/char_cat_DIFFUSE_v73.%04d.exr";
    ImageElement mock_element{test_path};
    mock_element.setFrames({1002, 1004});

    std::vector<std::string> expected_value = {
            "/mock/char_cat_DIFFUSE_v73.1002.exr",
            "/mock/char_cat_DIFFUSE_v73.1004.exr"
    };

    EXPECT_EQ(expected_value, mock_element.getPaths());
}


TEST(imageElement, test_getPaths_no_frames){
    std::string test_path = "/mock/char_cat_DIFFUSE_v73.exr";
    ImageElement mock_element{test_path};

    std::vector<std::string> expected_value = {"/mock/char_cat_DIFFUSE_v73.exr"};

    EXPECT_EQ(expected_value, mock_element.getPaths());
}


TEST(imageElement, test_is_equal){
    ImageElement a{"/mock/char_cat_DIFFUSE_v73.1078.exr"};
    ImageElement b{"/mock/char_cat_DIFFUSE_v73.1078.exr"};

    bool result = a == b;
    EXPECT_TRUE(result);
}

TEST(imageElement, test_is_not_equal){
    ImageElement a{"/mock/char_cat_DIFFUSE_v73.1078.exr"};
    ImageElement b{"/mock/char_cat_DIFFUSE_v74.1079.exr"};
    bool result = a == b;

    EXPECT_FALSE(result);
}

TEST(imageElement, test_merge_frames){
    ImageElement a{"/mock/char_cat_DIFFUSE_v73.1078.exr"};
    a.setFrames({103, 104, 102});

    ImageElement b{"/mock/char_cat_DIFFUSE_v73.1078.exr"};
    b.setFrames({101, 102});

    std::vector<int> expected_value = {101, 102, 103, 104};

    a.merge(b); // merge frame range.

    EXPECT_EQ(expected_value, a.getFrames());
}