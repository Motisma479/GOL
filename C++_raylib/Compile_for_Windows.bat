@echo off

set CMAKE_GENERATOR="MinGW Makefiles"
set CMAKE_BUILD_TYPE=Release
set CMAKE_BINARY_DIR=./out

cmake -B %CMAKE_BINARY_DIR% -G %CMAKE_GENERATOR%
cmake --build %CMAKE_BINARY_DIR% --config %CMAKE_BUILD_TYPE%