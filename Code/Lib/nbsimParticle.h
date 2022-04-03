#ifndef nbsimParticle_h
#define nbsimParticle_h
#include <Eigen/Dense>
#include <iostream>

/**
* \file nbsimParticle.h
* \brief Various Utilities.
* \ingroup utilities
*/
namespace nbsim
{
  class Particle{

    public:
    Particle();
    Particle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity);
    ~Particle();

    public:
    Eigen::Vector3d getPosition();
    Eigen::Vector3d getVelocity();
    void setPosition(const Eigen::Vector3d &position);
    void setVelocity(const Eigen::Vector3d &velocity);
    void integrateTimestep(const Eigen::Vector3d &acceleration, const double &timestep);
    std::string getName();
    void setName(const std::string &name);

    protected:
    Eigen::Vector3d m_position;
    Eigen::Vector3d m_velocity;
    std::string m_name = "undefined";

  };

} // end namespace

#endif
