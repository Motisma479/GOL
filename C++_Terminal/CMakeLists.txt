cmake_minimum_required(VERSION 3.8)
project(GOL)
set(CMAKE_CXX_STANDARD 17)

include_directories ("Headers")

set(SOURCES
    "Sources/main.cpp"
)

add_executable (${PROJECT_NAME} ${SOURCES})

#add flags to make the executable static
SET(FLAGS_LINKER "-static -static-libgcc -static-libstdc++")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS_LINKER}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG=1)
else()
    add_compile_definitions(DEBUG=0)
endif()

if (WIN32)
    add_compile_definitions(WINDOWS)
elseif (APPLE)
    add_compile_definitions(MACOS)
else()
    add_compile_definitions(LINUX)
endif()