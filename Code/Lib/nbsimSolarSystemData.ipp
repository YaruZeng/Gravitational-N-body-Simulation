/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimSolarSystemData_h
#define nbsimSolarSystemData_h

#include <array>
#include <string>
#include <Eigen/Dense>

/**
* \file nbsimSolarSystemData.h
* \brief Input Solar System Data for N-body Simulation.
* \ingroup utilities
*/
namespace nbsim
{

/**
* \brief Struct to store planet data
*/
struct Planet
{
  std::string name{};
  Eigen::Vector3d position{}; // position (AU)
  Eigen::Vector3d velocity{}; // velocity (AU/yr)
  double mu{}; // gravitational parameter G*m
};

/**
* \brief Array of Planet data making up Solar System
*/
const int NPLANETS = 9;
std::array<Planet, NPLANETS> solarSystemData = 
{ 
  {
    { "Sun", Eigen::Vector3d(-0.00670894, 0.0060565, 0.00010651),
      Eigen::Vector3d(-2.21245000e-03, -2.52969157e-03, 7.44511552e-05),
      39.4784 },
    { "Mercury", Eigen::Vector3d(0.230275, -0.35195738, -0.05088345),
      Eigen::Vector3d(3.31488, 11.06541681, 0.6141127),
      6.6156e-06 },
    { "Venus", Eigen::Vector3d(-0.453178, -0.56381468, 0.01805713),
      Eigen::Vector3d(5.85277, -4.48202274, -0.39906484),
      9.7499e-05 },
    { "Earth", Eigen::Vector3d(-1.85741000e-01, 9.72885512e-01, 4.83110862e-05),
      Eigen::Vector3d(-6.30094000, -1.06026870, -5.77226257e-06),
      0.000119632 },
    { "Mars", Eigen::Vector3d(0.614263, 1.38167319, 0.01368457),
      Eigen::Vector3d(-3.70135, 4.25305942, 0.17975581),
      1.28e-05 },
    { "Jupiter", Eigen::Vector3d(3.0346, -4.08224997, -0.05090904),
      Eigen::Vector3d(1.90073, 2.14771059, -0.05147114),
      0.03802 },
    { "Saturn", Eigen::Vector3d(5.4834, -8.33624023, -0.07325462),
      Eigen::Vector3d(1.47169, 1.29387179, -0.08122963),
      0.01138 },
    { "Uranus", Eigen::Vector3d(15.3436, 12.46732324, -0.15263367),
      Eigen::Vector3d(-1.0614, 0.92734223, 0.01718072),
      0.0017382 },
    { "Neptune", Eigen::Vector3d(29.4537, -5.2263084, -0.57110369),
      Eigen::Vector3d(0.163551, 1.13959835, -0.02716158),
      0.0020517 }
  }
};    

} // end namespace nbsim

#endif