#/*============================================================================
#
#  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

######################################################################
# Set the minimum CMake version.
######################################################################
set(PHAS0100ASSIGNMENT2_CMAKE_MINIMUM_REQUIRED_VERSION 3.5)
cmake_minimum_required(VERSION ${PHAS0100ASSIGNMENT2_CMAKE_MINIMUM_REQUIRED_VERSION})


###################################################################################
# Set some CMake Policies.
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details.
###################################################################################
set(project_policies )
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()


###############################################################################
# Setup project name, and version.
###############################################################################
project(PHAS0100ASSIGNMENT2 VERSION 0.0.0)


######################################################################
# Setup the path to load CMake macros, and extra CMake files.
# This means cmake can 'see' or 'use' files in the CMake folder.
######################################################################
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)


######################################################################
# Include extra CMake stuff for configuring this project.
######################################################################
include(mitkFunctionCheckCompilerFlags)


######################################################################
# Set main build options.
######################################################################
option(BUILD_TESTING "Build Unit tests." ON)
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)


######################################################################
# Setup Testing (dashboards etc.).
######################################################################
include(nbsimSetupTesting)


######################################################################
# Setting supported build types. Should ONLY be Release or Debug.
######################################################################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Valid options are Release or Debug" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug")
endif()

if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Debug"))
  message(FATAL_ERROR "Build type \"${CMAKE_BUILD_TYPE}\" is not supported.")
endif()

if(WIN32)
  # Restrict the generated configuration to be what we configured above.
  # No point creating project files for build types that will not compile.
  # Note: it's set to FORCE so that both CMAKE_BUILD_TYPE and CMAKE_CONFIGURATION_TYPES match up.
  set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "Build configurations to generate." FORCE)
  mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()


######################################################################
# Choose C++ standard. Currently 17.
######################################################################
set(PHAS0100ASSIGNMENT2_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS 0)
set(CMAKE_CXX_STANDARD ${PHAS0100ASSIGNMENT2_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED 1)

# This is necessary to avoid problems with compile feature checks.
# CMAKE_CXX_STANDARD seems to only set the -std=c++17 flag for targets.
# However, compile flag checks also need to be done with -std=c++11.
# The PHAS0100ASSIGNMENT2_CXX11_FLAG variable is also used for external projects
# build during the PHAS0100ASSIGNMENT2 super-build.
mitkFunctionCheckCompilerFlags("-std=c++17" PHAS0100ASSIGNMENT2_CXX17_FLAG)
if(NOT PHAS0100ASSIGNMENT2_CXX17_FLAG)
  # Older gcc compilers use -std=c++0x
  mitkFunctionCheckCompilerFlags("-std=c++17" PHAS0100ASSIGNMENT2_CXX17_FLAG)
endif()


######################################################################
# Force MSVC runtime. Depends on BUILD_SHARED_LIBS.
######################################################################
include(nbsimSetupMSVCRuntime)


######################################################################
# Print out where the source and binary folders
# are, just to make it really explicit.
######################################################################
message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")


######################################################################
# Additionally add the build folder, now we are building main project.
######################################################################
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})


######################################################################
# Copy some reference files to output.
######################################################################
configure_file(${CMAKE_SOURCE_DIR}/LICENSE.txt ${CMAKE_BINARY_DIR}/LICENSE.txt @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/LICENSE.txt DESTINATION . COMPONENT CONFIG)
configure_file(${CMAKE_SOURCE_DIR}/README.md ${CMAKE_BINARY_DIR}/README.md @ONLY)


######################################################################
# Organise module/plugin/etc projects better within the IDE.
######################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


######################################################################
# Add Optional Requirements
######################################################################
if(WIN32)
  set(_library_sub_dir "bin")
else()
  set(_library_sub_dir "lib")
endif()


######################################################################
# Compilation specific stuff, like flags etc.
######################################################################
if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX /W2")
  set(CMAKE_CXX_WARNING_LEVEL 2)
endif(WIN32)

if(WIN32 AND NOT BUILD_SHARED_LIBS)
  add_definitions(-DPHAS0100ASSIGNMENT2_STATIC)
endif()

if(UNIX)
  mitkFunctionCheckCompilerFlags("-Wno-deprecated-declarations" PHAS0100ASSIGNMENT2_NO_DEPRECATED_FLAG)
  if(PHAS0100ASSIGNMENT2_NO_DEPRECATED_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PHAS0100ASSIGNMENT2_NO_DEPRECATED_FLAG}" CACHE STRING "FLags used by the compiler during all build types." FORCE)
  endif()
  mitkFunctionCheckCompilerFlags("-Wno-ignored-attributes" PHAS0100ASSIGNMENT2_NO_IGNORED_ATTRIBUTES_FLAG)
  if(PHAS0100ASSIGNMENT2_NO_IGNORED_ATTRIBUTES_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PHAS0100ASSIGNMENT2_NO_IGNORED_ATTRIBUTES_FLAG}")
  endif()
endif()

######################################################################
# OpenMP is required for this assignment.
######################################################################
find_package(OpenMP REQUIRED)
  if(OPENMP_FOUND)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

######################################################################
# A few shortcuts for lists of libraries.
######################################################################
set(PHAS0100ASSIGNMENT2_LIBRARIES phas0100assignment2)
set(ALL_LIBRARIES ${PHAS0100ASSIGNMENT2_LIBRARIES})


######################################################################
# Set up a few paths.
######################################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(PHAS0100ASSIGNMENT2_INSTALL_LIB_DIR lib)
set(PHAS0100ASSIGNMENT2_INSTALL_INC_DIR include)
set(PHAS0100ASSIGNMENT2_INSTALL_BIN_DIR bin)

foreach(type LIBRARY RUNTIME ARCHIVE)
  set(output_dir ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_${type}_OUTPUT_DIRECTORY ${output_dir} CACHE INTERNAL "Single output directory for building all libraries.")
  mark_as_advanced(CMAKE_${type}_OUTPUT_DIRECTORY)
endforeach()

include_directories(${CMAKE_SOURCE_DIR}/Code/3rdParty/Eigen-3.2.2.1)
include_directories(${CMAKE_SOURCE_DIR}/Code/Lib)
include_directories(${CMAKE_BINARY_DIR})


######################################################################
# Add our main code folders. This is where all our functionality is.
######################################################################
add_subdirectory(Code)
if(BUILD_TESTING)
  set(TEMP_DIR ${CMAKE_BINARY_DIR}/Testing/Temporary)
  include_directories(${CMAKE_SOURCE_DIR}/Testing/)
  add_subdirectory(Testing)
endif()
