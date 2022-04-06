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
  nbsimMassiveParticle.cpp
  nbsimParticle.cpp
  nbsimException.cpp
  nbsimSimulator.cpp
  nbsimSolarSystem.cpp
  nbsimRandSystem.cpp
)

set(PHAS0100ASSIGNMENT2_LIBRARY_HDRS
  nbsimExceptionMacro.h
  nbsimSolarSystemData.ipp
)

add_library(${PHAS0100ASSIGNMENT2_LIBRARY_NAME} ${PHAS0100ASSIGNMENT2_LIBRARY_HDRS} ${PHAS0100ASSIGNMENT2_LIBRARY_SRCS})

target_link_libraries(${PHAS0100ASSIGNMENT2_LIBRARY_NAME} PRIVATE ${ALL_THIRD_PARTY_LIBRARIES})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PHAS0100ASSIGNMENT2_LIBRARY_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()