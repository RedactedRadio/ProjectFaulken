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
    src/PlayerActions.cpp
    src/PlayerSave.cpp
    src/Console.cpp
    src/ConsoleUI.cpp
    src/Game.cpp
    src/GameCommandHistory.cpp
    src/GameCommandParsing.cpp
    src/GameCommands.cpp
    src/GameEffects.cpp
    src/GameNavigation.cpp
    src/GameOver.cpp
    src/GameRooms.cpp
    src/MapBase.cpp
    src/MapBaseComputer.cpp
    src/MapBaseFacilities.cpp
    src/MapBaseOffice.cpp
    src/MapBaseZero.cpp
    src/TitleScreen.cpp
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 QUIET sdl2)
pkg_check_modules(SDL2_TTF QUIET SDL2_ttf)

if(SDL2_FOUND AND SDL2_TTF_FOUND)
    message(STATUS "SDL2 and SDL2_ttf found: building windowed UI support")
    list(APPEND SOURCES src/WindowUI.cpp)
    list(APPEND SOURCES src/WindowUIInput.cpp)
    list(APPEND SOURCES src/WindowUIOutput.cpp)
    list(APPEND SOURCES src/WindowUIRender.cpp)
    add_definitions(-DHAS_WINDOW_UI)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
    link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_TTF_LIBRARY_DIRS})
else()
    message(STATUS "SDL2 or SDL2_ttf not found: building console-only UI")
endif()

# Create executable
add_executable(faulken ${SOURCES})

if(SDL2_FOUND AND SDL2_TTF_FOUND)
    target_link_libraries(faulken PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
endif()

# Optional: Add compiler flags for better warnings
if(MSVC)
    target_compile_options(faulken PRIVATE /W4)
else()
    target_compile_options(faulken PRIVATE -Wall -Wextra -Wpedantic)
endif()
