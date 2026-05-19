cmake_minimum_required(VERSION 3.10)
project(ProjectFaulken_CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Player.cpp
    src/Console.cpp
    src/ConsoleUI.cpp
    src/Game.cpp
    src/GameOver.cpp
    src/MapBase.cpp
    src/TitleScreen.cpp
)

# Create executable
add_executable(faulken ${SOURCES})

# Optional: Add compiler flags for better warnings
if(MSVC)
    target_compile_options(faulken PRIVATE /W4)
else()
    target_compile_options(faulken PRIVATE -Wall -Wextra -Wpedantic)
endif()
