cmake_minimum_required(VERSION 3.24...3.30)
project(text_input)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    # makes initial build faster, clone this tag only
    GIT_SHALLOW TRUE         
)
FetchContent_MakeAvailable(raylib)

add_executable(text_input
    main.cpp
    textinput.cpp
    textinput.h
)

target_link_libraries(text_input PRIVATE raylib)

# Copy assets next to the built executable after every build
add_custom_command(TARGET text_input POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}
        $<TARGET_FILE_DIR:text_input>)