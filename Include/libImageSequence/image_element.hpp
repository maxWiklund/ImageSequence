//
// Created by max-wi on 21/07/2020.
//

#ifndef IMAGESEQUENCE_IMAGE_ELEMENT_HPP
#define IMAGESEQUENCE_IMAGE_ELEMENT_HPP

#ifdef _WIN32
    #define DIRECTORY_PATH_DELIMITER "\\"
#else
    #define DIRECTORY_PATH_DELIMITER "/"
#endif


#include <vector>
#include <string>


class ImageElement{
public:
    std::vector<int> frames;
    std::vector<int> udims;
    ImageElement(std::string file_path, std::string file_name);
    ImageElement(std::string file_path, std::string file_name, std::vector<int> frames);
    std::string basename();
    std::string dirname();
    std::string frameAt(int frame);
    std::string udimAt(int number);
    std::string framAndUdim(int frame, int udim);

    void setFrames(std::vector<int> frames);
    void setUdims(std::vector<int> udims);
    bool operator== (ImageElement *other);


private:
    ImageElement *merge(ImageElement *other);
    std::string file_path;
    std::string file_name;
    std::string tokenize_name(std::string file_name);
    std::string getFilePath();

};


#endif //IMAGESEQUENCE_IMAGE_ELEMENT_HPP
