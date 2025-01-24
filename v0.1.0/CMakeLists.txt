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

# Ensure CLI11 is available
if(NOT TARGET CLI11::CLI11)
  message(FATAL_ERROR "CLI11 library was not successfully fetched and made available.")
endif()

# Copy CLI11 headers to the project's include directory
add_custom_target(copy_cli11_headers ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CLI11_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include
  COMMENT "Copying CLI11 headers to the project's include directory"
)

set(SOURCES
    main.cpp
)

add_executable(netcalc ${SOURCES})

# Ensure the headers are copied before building the target
add_dependencies(netcalc copy_cli11_headers)

target_precompile_headers(netcalc PRIVATE
    <iostream>
    <string>
    <bitset>
)

# Link the CLI11 library to the netcalc target
target_link_libraries(netcalc PRIVATE CLI11::CLI11)

# Ensure the include directories are set correctly
target_include_directories(netcalc PRIVATE ${PROJECT_SOURCE_DIR}/include)

if(MSVC)
  target_compile_options(netcalc PRIVATE /W4)
else()
  target_compile_options(netcalc PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS netcalc DESTINATION bin)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CLI11 include directory: ${PROJECT_SOURCE_DIR}/include")