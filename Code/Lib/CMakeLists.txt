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

set(PHAS0100ASSIGNMENT2_LIBRARY_NAME phas0100assignment2)

set(PHAS0100ASSIGNMENT2_LIBRARY_SRCS
  nbsimBasicTypes.cpp
  nbsimMyFunctions.cpp
  nbsimException.cpp
)

set(PHAS0100ASSIGNMENT2_LIBRARY_HDRS
  nbsimExceptionMacro.h
  nbsimSolarSystemData.ipp
)

add_library(${PHAS0100ASSIGNMENT2_LIBRARY_NAME} ${PHAS0100ASSIGNMENT2_LIBRARY_HDRS} ${PHAS0100ASSIGNMENT2_LIBRARY_SRCS})

if(BUILD_SHARED_LIBS)
  if(WIN32)
    add_definitions(-DPHAS0100ASSIGNMENT2_WINDOWS_EXPORT)
  endif(WIN32)
endif(BUILD_SHARED_LIBS)

target_link_libraries(${PHAS0100ASSIGNMENT2_LIBRARY_NAME} PRIVATE ${ALL_THIRD_PARTY_LIBRARIES})

