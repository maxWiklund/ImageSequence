# Copyright (C) 2020  Max Wiklund
#
# Licensed under the Apache License, Version 2.0 (the “License”);
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an “AS IS” BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import copy
import os

import PyImageSequence

PROJECT_ROOT = os.path.dirname(__file__)


seq = PyImageSequence.ImageElement(path="/mock/path/file.1003.exr")
other = PyImageSequence.ImageElement(path="/mock/path/file.1008.exr")

assert seq == other
assert seq.basename() == "file.%04d.exr"
assert seq.dirname() == "/mock/path"
assert seq.frames == [1003]

# Check property
seq.frames = list(range(1, 4))
assert seq.frames == [1, 2, 3]

# Check copy
a = PyImageSequence.ImageElement(path="/mock/file.1234.exr")
b = copy.copy(a)  # Copy c++ class.
assert a == b
b.name = "new_name"
assert b.name == "new_name" and a != b

u = PyImageSequence.ImageElement("/mock/path/image.exr")
v = copy.deepcopy(u)
assert u == v
u.name = "u"
v.name = "v"
assert u.name == "u" and v.name == "v" and v != u


# Test set directory.
x = PyImageSequence.ImageElement("/mock/path/file.exr")
x.setDirName("/new/dir/")
assert x.getFilePath() == "/new/dir/file.exr"


# Test scandir.
ROOT_PATH = os.path.join(os.path.dirname(__file__), "tests/textures")
found_files = PyImageSequence.scandir(path=ROOT_PATH)

# Create expected result.
se1 = PyImageSequence.ImageElement(path=os.path.join(PROJECT_ROOT, "tests/textures/char_dog_BUMP.%04d.exr"))
se2 = PyImageSequence.ImageElement(path=os.path.join(PROJECT_ROOT, "tests/textures/file_name-test.png"))
se3 = PyImageSequence.ImageElement(path=os.path.join(PROJECT_ROOT, "tests/textures/char_dog_DIFFUSE.%04d.exr"))
se1.frames = [1002, 1003]
se3.frames = [1001, 1002]

EXPECTED_RESULTS = [
    se1,
    se2,
    se3
]

assert EXPECTED_RESULTS == found_files
assert found_files[0].frames == se1.frames
assert found_files[1].frames == se2.frames
assert found_files[2].frames == se3.frames


# Test findFramesOnDisk
abc = PyImageSequence.ImageElement(os.path.join(ROOT_PATH, "char_dog_BUMP.%04d.exr"))
abc.findFramesOnDisk()
assert abc.frames == [1002, 1003]
