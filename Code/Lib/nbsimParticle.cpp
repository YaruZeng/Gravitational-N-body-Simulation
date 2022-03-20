/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "nbsimParticle.h"
#include <iostream>

namespace nbsim {

//-----------------------------------------------------------------------------
  Particle::Particle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity){
    this->m_position = position;
    this->m_velocity = velocity;
  }

  Particle::~Particle(){}

  Eigen::Vector3d Particle::getPosition(){
    return m_position;
  }

  Eigen::Vector3d Particle::getVelocity(){
    return m_velocity;
  }

  void Particle::integrateTimestep(const Eigen::Vector3d &acceleration, const double &timestep){

    Eigen::Vector3d position_new(0,0,0);
    Eigen::Vector3d velocity_new(0,0,0);
    position_new = m_position +  m_velocity * timestep;
    velocity_new = m_velocity + acceleration * timestep;
    m_position = position_new;
    m_velocity = velocity_new;
    
  }

} // end namespace
