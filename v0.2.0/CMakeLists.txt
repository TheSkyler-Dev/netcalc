cmake_minimum_required(VERSION 3.16.0)

project(netcalc VERSION 0.2.0 LANGUAGES CXX)

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

# Fetching fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.1.4
)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  
  # Patch the fmt CMakeLists.txt to use underscore instead of dash
  file(READ "${fmt_SOURCE_DIR}/CMakeLists.txt" fmt_cmake_content)
  string(REPLACE "COMPONENT fmt-core" "COMPONENT fmt_core" fmt_cmake_content_patched "${fmt_cmake_content}")
  file(WRITE "${fmt_SOURCE_DIR}/CMakeLists.txt" "${fmt_cmake_content_patched}")
  
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
endif()

# Then update the display name
set(CPACK_COMPONENT_FMT_CORE_DISPLAY_NAME "fmt-core")

FetchContent_MakeAvailable(fmt)

if(NOT TARGET fmt::fmt)
  message(FATAL_ERROR "fmt library was not successfully fetched and made available.")
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
target_link_libraries(netcalc PRIVATE CLI11::CLI11 fmt::fmt)

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

# Set component display name mapping to keep original name in display
set(CPACK_COMPONENT_FMT_CORE_DISPLAY_NAME "fmt-core")
set(CPACK_COMPONENT_FMT_CORE_DESCRIPTION "The fmt C++ formatting library")

# CPack configuration
include(CPack)
include(InstallRequiredSystemLibraries)

# Set package metadata
set(CPACK_PACKAGE_NAME "netcalc")
set(CPACK_PACKAGE_VENDOR "TheSkyler-Dev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A network calculator utility")
set(CPACK_PACKAGE_DESCRIPTION "netcalc is a command-line utility for performing various network calculations such as subnet analysis, IP conversions, and more.")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "netcalc")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_CONTACT "TheSkyler-Dev")

# RPM specific settings
set(CPACK_RPM_PACKAGE_LICENSE "GPL-3.0")
set(CPACK_RPM_PACKAGE_GROUP "Applications/Networking")
set(CPACK_RPM_PACKAGE_REQUIRES "glibc, libstdc++")
set(CPACK_RPM_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION}")

# Windows NSIS specific settings
set(CPACK_NSIS_DISPLAY_NAME "Network Calculator")
set(CPACK_NSIS_PACKAGE_NAME "netcalc")
set(CPACK_NSIS_HELP_LINK "https://github.com/TheSkyler-Dev/netcalc")
set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/TheSkyler-Dev/netcalc")
set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

# Platform-specific generator selection
if(WIN32)
set(CPACK_GENERATOR "NSIS")
else()
set(CPACK_GENERATOR "RPM")
endif()

# Enable WiX generator as alternative for Windows
if(WIN32)
list(APPEND CPACK_GENERATOR "WIX") 
set(CPACK_WIX_UPGRADE_GUID "8CF6A9DB-6B5E-4FD0-AC85-5962D7D45EF1")

endif()