# Building

## Dependencies 
Before you can install the library you need to install the dependencies.

|    Name    |    Status   |   Version   |
|:----------:|:-----------:|:-----------:|
|pybinding 11|  Required   |    1.0      |
|   boost    |  Required   |    1.4      |
|   python   |  Optional   | 2.7 - 3.8   |
|   cmake    |  Required   |    3.16     |

## Installation
```
git clone git@github.com:maxWiklund/ImageSequence.git
cd ImageSequence
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make install 
```



