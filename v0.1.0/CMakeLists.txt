cmake_minimum_required(VERSION 3.16.0)

project(netcalc VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.4.2
)
FetchContent_MakeAvailable(CLI11)

set(SOURCES
    main.cpp
)

add_executable(netcalc ${SOURCES})

target_precompile_headers(netcalc PRIVATE
    <iostream>
    <string>
    CLI11.hpp
    <stdexcept>
)

if(MSVC)
  target_compile_options(Multiconvert PRIVATE /W4)
else()
  target_compile_options(netcalc PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS netcalc DESTINATION bin)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Include directories: ${PROJECT_SOURCE_DIR}/include")