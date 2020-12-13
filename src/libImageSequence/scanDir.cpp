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

#include "libImageSequence/scanDir.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/unordered_map.hpp>

#include <iostream>


bool endswith(const std::string &path, const std::vector<std::string> &extensions){
    for(auto &ext : extensions){
        if (boost::algorithm::ends_with(path, ext)){
            return true;
        }
    }
    return false;
}


/*! Scan directory for image sequences and generate elements for them.
 *
 * @param path: Directory path to scan.
 * @param extensions: File types to filter for. If array is empty all file types will be allowed.
 * @return:
 */
std::vector<ImageElement> scandir(const std::string &path, const std::vector<std::string> &extensions) {
    std::vector<ImageElement> foundImages;
    if (!boost::filesystem::is_directory(path)){
        std::cerr << "File path is \"" << path << "\" not a directory. " << std::endl;
        return foundImages;
    }
    boost::unordered_map<std::string, ImageElement> table{};

    for (auto & item : boost::filesystem::directory_iterator(path)){

        // If filter is applied check if file ends with extensions.
        if(!extensions.empty() && !endswith(item.path().string(), extensions)){
            continue;
        }

        if (boost::filesystem::is_regular_file(item.path())){
            ImageElement element{item.path().string()};

            auto search = table.find(element.basename());  // Try to find the file pattern in hashmap.
            if (search != table.end()){  // Element found.
                ImageElement &existingElement = search->second;
                existingElement.merge(element);  // Update existing element.
                continue;
            } else{
                table.insert({element.basename(), element});
            }
        }
    }
    for (const auto& p: table){
        foundImages.emplace_back(p.second);
    }

    return foundImages;
}
