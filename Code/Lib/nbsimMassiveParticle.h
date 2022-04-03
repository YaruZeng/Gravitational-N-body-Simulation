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
      double getMu(); //returns the gravitational parameter
      void setMu(const double &mu);
      void addAttractor(std::shared_ptr<MassiveParticle> attractor); //add an attractor
      void removeAttractor(std::shared_ptr<MassiveParticle> attractor); //remove an attractor
      void calculateAcceleration(); //calculates the gravitational acceleration and stores the result as a Vector3d data member
      void integrateTimestep(const double &timestep); //updates the position and velocity as though a duration of length timestep has passed

      private:
      std::vector<std::shared_ptr<MassiveParticle>> vec_attractors;
      double m_mu;
      Eigen::Vector3d m_acceleration;
      
  };

} // end namespace

#endif
