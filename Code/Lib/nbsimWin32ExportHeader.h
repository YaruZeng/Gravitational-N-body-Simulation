/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimWin32ExportHeader_h
#define nbsimWin32ExportHeader_h

/**
* \file nbsimWin32ExportHeader.h
* \brief Header to sort Windows dllexport/dllimport.
*/

#if (defined(_WIN32) || defined(WIN32)) && !defined(PHAS0100ASSIGNMENT2_STATIC)
  #ifdef PHAS0100ASSIGNMENT2_WINDOWS_EXPORT
    #define PHAS0100ASSIGNMENT2_WINEXPORT __declspec(dllexport)
  #else
    #define PHAS0100ASSIGNMENT2_WINEXPORT __declspec(dllimport)
  #endif  /* PHAS0100ASSIGNMENT2_WINEXPORT */
#else
/* linux/mac needs nothing */
  #define PHAS0100ASSIGNMENT2_WINEXPORT
#endif

#endif
