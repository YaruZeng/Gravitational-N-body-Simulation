/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimParticle_h
#define nbsimParticle_h
#include <Eigen/Dense>

/**
* \file nbsimParticle.h
* \brief Various Utilities.
* \ingroup utilities
*/
namespace nbsim
{
class Particle{

  public:
  Particle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity);
  ~Particle();
  Eigen::Vector3d getPosition();
  Eigen::Vector3d getVelocity();
  void integrateTimestep(const Eigen::Vector3d &acceleration, const double &timestep);

  private:
  Eigen::Vector3d m_position;
  Eigen::Vector3d m_velocity;

};
/**
* \brief My first function, adds two integers.
*/
int MyFirstAddFunction(int a, int b);

} // end namespace

#endif
