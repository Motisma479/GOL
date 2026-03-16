cmake_minimum_required(VERSION 3.8)
project(GOL)
set(CMAKE_CXX_STANDARD 17)

include_directories ("Headers")

set(SOURCES
    "Sources/main.cpp"
)

add_subdirectory(Externals/raylib)

add_executable (${PROJECT_NAME} ${SOURCES})

#add flags to make the executable static
SET(FLAGS_LINKER "-static -static-libgcc -static-libstdc++")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS_LINKER}")

target_link_libraries(${PROJECT_NAME} raylib)