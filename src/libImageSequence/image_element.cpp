//
// Created by max-wi on 21/07/2020.
//
#include "libImageSequence/image_element.hpp"

#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;

sregex file_name_re = sregex::compile(
        "(?P<name>[a-zA-Z_\\-\\d\\[\\]]+)"
        "(\\.(?P<frame>\\d+))?"
        "(\\.(?P<udim>\\d+))?"
        "(?P<ext>\\.[a-zA-Z_\\d]+)$"
);


ImageElement::ImageElement(std::string file_path, std::string file_name) {
    this->file_path = file_path;
    this->file_name = this->tokenize_name(file_name);
}

bool ImageElement::operator==(ImageElement *other) {
    return this->file_name == other->file_name;
}


std::string ImageElement::tokenize_name(std::string file_name) {
    smatch match_result;
    if(regex_search(file_name, match_result, file_name_re))
    {
        std::string format_frame = "";
        std::string format_udim = "";
        std::string name = match_result["name"];
        std::string frame = match_result["frame"];
        std::string udim = match_result["udim"];
        std::string ext = match_result["ext"];
        // Save frame
        if (!frame.empty()) {
            this->frames.push_back(std::stoi( frame ));
            format_frame = ".%04d";
        }
        // Save udim.
        if (!udim.empty()) {
            this->udims.push_back(std::stoi(udim));
            format_udim = ".<UDIM>";
        }

        return name + format_frame + format_udim + ext;  // Construct new name.
    }
    return file_name;
}


std::string ImageElement::basename() {
    return this->file_name;
}


std::string ImageElement::dirname() {
    return this->file_path;
}


std::string ImageElement::getFilePath() {
    return this->file_path + DIRECTORY_PATH_DELIMITER + this->file_name;
}


ImageElement *ImageElement::merge(ImageElement *other) {

    std::vector<int> frame_range = this->frames;
    std::vector<int> udim_range = this->udims;

    frame_range.insert(frame_range.end(), other->frames.begin(), other->frames.end());  // concatenate frame ranges.
    udim_range.insert(udim_range.end(), other->udims.begin(), other->udims.end());  // concatenate frame ranges.
    ImageElement *merged_element = new ImageElement(this->file_path, file_name);
    merged_element->setFrames(frame_range);
    merged_element->setUdims(udim_range);
    return merged_element;
}


void ImageElement::setFrames(std::vector<int> frames) {
    this->frames = frames;
}


void ImageElement::setUdims(std::vector<int> udims) {
    this->udims = udims;
}

std::string ImageElement::frameAt(int frame) {
    boost::format formated_frame = boost::format(this->getFilePath()) %frame;
    return formated_frame.str();
}


std::string ImageElement::udimAt(int number) {
    boost::format udim_number = boost::format("%04d") %number;
    boost::regex udim_re("(<UDIM>)");
    return boost::regex_replace(this->getFilePath(), udim_re, udim_number.str());
}

std::string ImageElement::framAndUdim(int frame, int udim) {
    boost::format formated_fram_udim = boost::format(this->udimAt(udim)) %frame;
    return formated_fram_udim.str();
}
