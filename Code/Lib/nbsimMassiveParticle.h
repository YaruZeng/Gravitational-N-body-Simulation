#ifndef nbsimMassiveParticle_h
#define nbsimMassiveParticle_h
#include "nbsimParticle.h"
#include <memory>
#include <iostream>
#include <vector>

namespace nbsim{

    class MassiveParticle: public nbsim::Particle{

      public:
      using Particle::Particle;
      MassiveParticle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &mu);
      MassiveParticle(const std::string &name, const Eigen::Vector3d &position, const Eigen::Vector3d &velocity, const double &mu);

      public:

      //get the gravitational parameter
      double getMu(); 

      //set the gravitational parameter
      void setMu(const double &mu);

      //add an attractor
      void addAttractor(std::shared_ptr<MassiveParticle> attractor); 

      //remove an attractor
      void removeAttractor(std::shared_ptr<MassiveParticle> attractor); 

      //calculate the gravitational acceleration
      void calculateAcceleration(); 

      //update the position and velocity after a timestep has passed
      void integrateTimestep(const double &timestep); 

      private:
      std::vector<std::shared_ptr<MassiveParticle>> vec_attractors;
      double m_mu;
      Eigen::Vector3d m_acceleration;
      
  };

} // end namespace

#endif
