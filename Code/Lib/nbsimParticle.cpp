#include "nbsimParticle.h"
#include <iostream>

namespace nbsim {

  Particle::Particle(){
    m_position = Eigen::Vector3d (0,0,0);
    m_velocity = Eigen::Vector3d (0,0,0);
  }

  Particle::Particle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity){
    m_position = position;
    m_velocity = velocity;
  }

  Particle::~Particle(){}

  Eigen::Vector3d Particle::getPosition(){
    return m_position;
  }

  Eigen::Vector3d Particle::getVelocity(){
    return m_velocity;
  }

  void Particle::setPosition(const Eigen::Vector3d &position){
    m_position = position;
  }

  void Particle::setVelocity(const Eigen::Vector3d &velocity){
    m_velocity = velocity;
  }
  
  void Particle::integrateTimestep(const Eigen::Vector3d &acceleration, const double &timestep){

    Eigen::Vector3d position_new(0,0,0);
    Eigen::Vector3d velocity_new(0,0,0);
    position_new = m_position +  m_velocity * timestep;
    velocity_new = m_velocity + acceleration * timestep;
    m_position = position_new;
    m_velocity = velocity_new;
    
  }

  std::string Particle::getName(){
    return m_name;
  }

  void Particle::setName(const std::string &name){
    m_name = name;
  }

} // end namespace
