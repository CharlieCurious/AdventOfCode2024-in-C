cmake_minimum_required(VERSION 3.22.1)

project(AdventOfCode2024)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Needed for proper nvim lsp functioning.
set(CMAKE_BUILD_TYPE Debug)

set(DAY "day_2" CACHE STRING "Day to compile")

# Include custom CMake functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(AddAdventDay)
include(AddDayTest)

add_subdirectory(solutions)

option(ENABLE_TESTS "Enable building tests" ON)
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(dependencies/unity)
    add_subdirectory(tests)
endif()

