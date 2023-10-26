# Conway's Game of Life (C++ <U>__Terminal__</U> Edition)

## ⭐ About the Project

This project is a Conway's Game of Life. I made it because I like this game so I decide to make some versions.

- __Some Characteristics :__

    The Code is written in [![C++](https://img.shields.io/badge/C%2B%2B-v17-blue)](https://isocpp.org/) and compilled with [![CMake](https://img.shields.io/badge/CMake-v3.8-blue?labelColor=gray&style=flat)](https://cmake.org/). It should be Cross Platform with windows and Linux.

## ☕ Getting Started

### Prequisites

You will need CMake v3.8+ and a c++ compiler.

### Installation

- Dowloading the release :

    Go find the edition you want in [the latest release](../../releases/latest) and download it.

- With Command : 

    ```bash
    cmake -B OUT_DIR -G CMAKE_GENERATOR
    cmake --build OUT_DIR --config BUILD_TYPE
    ```
- Using the script :

    You can change some option by editing the script.
    </br>`CMAKE_GENERATOR` by default is `"MinGW Makefiles"`.
    </br>`CMAKE_BUILD_TYPE` by default is `Release`. It's the build type of the executable.
    </br>`CMAKE_BINARY_DIR` by default is `./out`. It's the folder in which the executable will be generated.

    - On Windows :

        You can launch `Compile_for_Windows.bat`, or in a terminal execute :

        ```bash
        .\Compile_for_Windows.bat
        ```

    - On Linux :

        In a terminal execute :

        ```bash
        .\Compile_for_Linux.sh
        ```

## 📄 License
- [__MIT License__](LICENSE)