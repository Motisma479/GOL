cmake_minimum_required(VERSION 3.8)
project(GOL)
set(CMAKE_CXX_STANDARD 20)

include_directories ("Headers")
add_compile_definitions(GOL_VERSION="1.0.0")

set(SOURCES
    "Sources/main.cpp"
    "Sources/App.cpp"

    "Sources/Cell.cpp"
    "Sources/Chunk.cpp"
    "Sources/Camera.cpp"

    "Sources/UI/Button.cpp"
    "Sources/UI/Slider.cpp"
)

add_subdirectory(Externals/raylib)

add_executable (${PROJECT_NAME} ${SOURCES})

#add flags to make the executable static
SET(FLAGS_LINKER "-static -static-libgcc -static-libstdc++")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS_LINKER}")

target_compile_definitions(raylib PRIVATE GRAPHICS_API_OPENGL_43)
target_link_libraries(${PROJECT_NAME} raylib)