# ESP32 sample project with C++ support

(Below is short explanation of remaining files in the project folder.
README.md file in the upper level 'examples' directory for more information about examples.)

## How to use example
We encourage the users to use the example as a template for the new projects.
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Example folder contents

The project **sample_project** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── sdkconfig
├── main/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── main.hpp
│   └── src/
│       └── main.cpp
├── bsp/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── bsp_xxx.hpp
│   └── src/
│       └── bsp_xxx.cpp
├── build/                     Build output directory
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.
