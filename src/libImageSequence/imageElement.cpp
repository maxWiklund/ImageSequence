// Copyright (C) 2020  Max Wiklund
//
// Licensed under the Apache License, Version 2.0 (the “License”);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an “AS IS” BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "libImageSequence/imageElement.hpp"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <iostream>


using namespace boost::xpressive;


/*! Regex to extract name and optional frame information.*/
const sregex kFileNameRE = sregex::compile(
        "(?P<name>[\\w\\-\\[\\]]+)"
        "(\\.((?P<frame>\\d+)|"
        "(?P<token>((%0\\d+d)|([#@]+)))))?"
        "(?P<ext>\\.\\w+)$"
);


/*! Initialize class and parse file path.
 *
 * @param: Path to file.
 */
ImageElement::ImageElement(const std::string &path) {
    this->filePath = boost::filesystem::path(path).parent_path().string();
    parseName(boost::filesystem::path(path).filename().string());
}


ImageElement::ImageElement() {
}


ImageElement::~ImageElement() {
}


/*! Extract file name, frame number (optional), file extension from file name.
 *
 * @param filename: File name to parse.
 */
void ImageElement::parseName(const std::string &filename) {
    smatch match_result;
    if(regex_search(filename, match_result, kFileNameRE)){
        this->name = match_result["name"];
        this->framePadding = match_result["token"];
        std::string frame = match_result["frame"];
        // Save frame.
        if (!frame.empty()) {
            this->frames.push_back(std::stoi(frame));
        }
        this->extension = match_result["ext"];
    } else {
        std::cerr << "Error: " << filename << " Invalid file name." << std::endl;
    }
}


/*! Create file name.
 *
 * @return: Reconstructed file name.
 */
std::string ImageElement::buildName() {
    std::string suffix;
    if(!this->framePadding.empty() || !this->frames.empty()) {
        suffix = ".%04d" + this->extension;
    } else{
        suffix = this->extension;
    }
    return this->name + suffix;
}


/*! Get serialization file path.
 *
 * @return: File path with frame token.
 */
std::string ImageElement::getFilePath() {
    boost::filesystem::path fullPath = boost::filesystem::path(this->filePath) / this->buildName();
    return fullPath.string();
}


/*! Fined frames on disk for element.
 *
 * @return: False if no frames found else true.
 */
bool ImageElement::findFramesOnDisk() {
    // No frame toke found (eg .%04d or ####).
    if(this->filePath.empty()){
        std::cerr << "Error ImageElement does not have a path." << std::endl;
        return false;
    }

    if (this->framePadding.empty()){
        return false;
    }

    for (auto &item : boost::filesystem::directory_iterator(this->filePath)){
        if(boost::filesystem::is_regular_file(item.path())){
            ImageElement element(item.path().string());
            if (*this == element){
                this->merge(element);
            }
        }
    }
    return true;
}


/*! Get head of file path.
 * This is probably redundant.
 *
 * @return: Name of file.
 */
std::string ImageElement::basename() {
    return this->buildName();
}


/*! Get file path without head.
 * This is probably redundant.
 *
 * @return: Directory path of file.
 */
std::string ImageElement::dirname() {
    return this->filePath;
}


/*! Set new directory.
 *
 * @param path: New directory path.
 */
void ImageElement::setDirName(const std::string &path) {
    this->filePath = path;
}


/*! Format file path with frame number.
 *
 * @param frame: frame number to use.
 * @return: Formatted file path with frame number.
 */
std::string ImageElement::evalAtFrame(const int &frame) {
    boost::format fmt = boost::format(this->getFilePath()) %frame;
    return fmt.str();
}


/*! Create file paths from frames.
 *
 * @return: Vector with file paths with frames.
 */
std::vector<std::string> ImageElement::getPaths() {
    std::vector<std::string> allFilePaths;
    for (int frame : this->frames){
        allFilePaths.push_back(this->evalAtFrame(frame));
    }
    if (allFilePaths.empty()){
        // No frames exists.
        allFilePaths.push_back(this->getFilePath());
    }

    return allFilePaths;
}


/*!Compare serialization elements file path with other element.
 *
 * @param other: Element to compare to.
 * @return: True if equal else false.
 */
bool ImageElement::operator==(ImageElement &other) {
    return this->getFilePath() == other.getFilePath();
}


/*! Update element with frame's from other element.
 *
 * @param other: Element to merge.
 */
void ImageElement::merge(ImageElement &other) {
    std::vector<int> otherFrames = other.getFrames();
   this->frames.insert(this->frames.end(), otherFrames.begin(), otherFrames.end());
   this->upToDate = false;
}


/*! Get element frames.
 *
 * @return: Frames.
 */
std::vector<int> ImageElement::getFrames() {
    if (!this->upToDate){
        // Sort frames and remove duplicates.
        std::sort(this->frames.begin(), this->frames.end());
        this->frames.erase(std::unique(this->frames.begin(), this->frames.end()), this->frames.end());
        this->upToDate = true;
    }
    return this->frames;
}


/*! Set element frames.
 *
 * @param frames: Frames to set.
 */
void ImageElement::setFrames(const std::vector<int> &frames) {
    this->frames = frames;
    this->upToDate = false;
}
