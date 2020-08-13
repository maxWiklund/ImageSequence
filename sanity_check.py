import copy
import PyImageSequence

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


def testFunc():
    for imageSeq in PyImageSequence.scandir(path="/home/max-wi/dev/rnd/textures"):
        pass


import cProfile
cProfile.run("testFunc()")
