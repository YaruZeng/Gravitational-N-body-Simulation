#include "nbsimMassiveParticle.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <memory>

namespace nbsim {

  MassiveParticle::MassiveParticle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &mu){
    m_position = position;
    m_velocity = velocity;
    m_mu = mu;
  }

  MassiveParticle::MassiveParticle(const std::string &name, const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &mu){
    m_name = name;
    m_position = position;
    m_velocity = velocity;
    m_mu = mu;
  }

  double MassiveParticle::getMu(){
    return m_mu;
  }

  void MassiveParticle::setMu(const double &mu){
    m_mu = mu;
  }

  void MassiveParticle::addAttractor(std::shared_ptr<MassiveParticle> attractor){
    vec_attractors.push_back(attractor);
  }

  void MassiveParticle::removeAttractor(std::shared_ptr<MassiveParticle> attractor){
    vec_attractors.erase(std::remove(vec_attractors.begin(), vec_attractors.end(), attractor), vec_attractors.end());
  }

  void MassiveParticle::calculateAcceleration(){
    
    if (vec_attractors.size() == 0){
      m_acceleration = Eigen::Vector3d(0,0,0);
    }
    else{
      m_acceleration = Eigen::Vector3d(0,0,0);
      Eigen::Vector3d tmp_acceleration(0,0,0);

      for(auto attractor:vec_attractors){
        Eigen::Vector3d tmp_r(0,0,0);
        tmp_r = m_position - (*attractor).getPosition();
        tmp_acceleration = - (*attractor).getMu() / (tmp_r.cwiseAbs2().sum()) * tmp_r / std::sqrt(tmp_r.cwiseAbs2().sum());
        m_acceleration += tmp_acceleration; 
      }
    }
  }

  void MassiveParticle::integrateTimestep(const double &timestep){

    Eigen::Vector3d position_new(0,0,0);
    Eigen::Vector3d velocity_new(0,0,0);
    position_new = m_position + m_velocity * timestep;
    velocity_new = m_velocity + m_acceleration * timestep;
    m_position = position_new;
    m_velocity = velocity_new;

  } 


} // end namespace
