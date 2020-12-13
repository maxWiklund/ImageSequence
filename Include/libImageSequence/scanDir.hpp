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

#ifndef SCANDIR_HPP
#define SCANDIR_HPP

#include "libImageSequence/imageElement.hpp"

#include <vector>

/*! Scan directory for Images.
 *
 * @param path: Directory to scan for Images.
 * @param extensions: File types to filter for. If array is empty all file types will be allowed.
 * @return: Found image elements.
 */
std::vector<ImageElement> scandir(const std::string &path, const std::vector<std::string> &extensions={});

#endif //SCANDIR_HPP
