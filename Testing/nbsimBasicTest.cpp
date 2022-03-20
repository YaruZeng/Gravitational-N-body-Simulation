/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include <iostream>
#include <vector>
#include <cmath>

TEST_CASE( "Particle", "[Test of motion]" ) {

  Eigen::Vector3d p1(0,0,0);
  Eigen::Vector3d v1(1,1,1);
  nbsim::Particle particle1(p1,v1);

  //Test for a = 0

  Eigen::Vector3d acceleration1(0,0,0);
  double timestep1 = 1;
  particle1.integrateTimestep(acceleration1, timestep1);

  Eigen::Vector3d expect_p1(1,1,1);
  Eigen::Vector3d expect_v1(1,1,1);
  REQUIRE(particle1.getPosition() == expect_p1);
  REQUIRE(particle1.getVelocity() == expect_v1);

  //Test for a = const

  Eigen::Vector3d acceleration2(0,2,1);
  double timestep2 = 2;
  particle1.integrateTimestep(acceleration2, timestep2);

  Eigen::Vector3d expect_p2(3,3,3);
  Eigen::Vector3d expect_v2(1,5,3);
  REQUIRE(particle1.getPosition() == expect_p2);
  REQUIRE(particle1.getVelocity() == expect_v2);

  //Test for a = -x(t)

  Eigen::Vector3d p2(1,0,0);
  Eigen::Vector3d v2(0,1,0);
  nbsim::Particle particle2(p2,v2);
  double timestep3 = 2*M_PI/1000;
  for (int i = 0; i < 1000; ++i)
  {
    Eigen::Vector3d acceleration3 = -particle2.getPosition();
    particle2.integrateTimestep(acceleration3, timestep3);
  }

  Eigen::Vector3d expect_p3(1,0,0);
  Eigen::Vector3d expect_v3(0,1,0);
  std::cout << "particle2.getPosition(): " << particle2.getPosition() << std::endl;
  std::cout << "particle2.getVelocity(): " << particle2.getVelocity() << std::endl;
  REQUIRE(expect_p3.isApprox(particle2.getPosition(), 0.1));
  REQUIRE(expect_v3.isApprox(particle2.getVelocity(), 0.1));
  

}
