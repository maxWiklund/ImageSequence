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
#include "libImageSequence/scanDir.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

std::vector<std::string> kStringList;

PYBIND11_MODULE(PyImageSequence, module) {
    // ImageElement class.
    pybind11::class_<ImageElement>(module, "ImageElement")
            .def_property("frames",
                pybind11::cpp_function(&ImageElement::getFrames, pybind11::return_value_policy::copy),
                pybind11::cpp_function(&ImageElement::setFrames)
                )
            .def(pybind11::init<const std::string &>(), pybind11::arg("path"))
            .def("basename", &ImageElement::basename)
            .def("dirname", &ImageElement::dirname)
            .def("setDirName", &ImageElement::setDirName, pybind11::arg("path"))
            .def_readwrite("name", &ImageElement::name)
            .def_readwrite("extension", &ImageElement::extension)
            .def("getFilePath", &ImageElement::getFilePath, "Return serialized file path.")
            .def("getPaths", &ImageElement::getPaths, "Get all sequence file paths for this object.")
            .def("evalAtFrame", &ImageElement::evalAtFrame, pybind11::arg("frame"))
            .def("findFramesOnDisk", &ImageElement::findFramesOnDisk)
            .def("__repr__", [](ImageElement &self){
                return "ImageElement(path=\"" + self.getFilePath() + "\")";
            })

            .def("__copy__", [](ImageElement &imSeq) {return imSeq;})
            .def("__deepcopy__", [](ImageElement &imSeq, const pybind11::object&) {return imSeq;})
            .def("__eq__", [](ImageElement &imSeq, const pybind11::object &rhs) {
               ImageElement other = pybind11::cast<ImageElement>(rhs);
                return imSeq == other;
            });

    module.def("scandir",
               &scandir,
               "Scan directory for images.",
               pybind11::arg("path"),
               pybind11::arg("extensions")=kStringList);
}
