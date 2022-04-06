#ifndef nbsimParticle_h
#define nbsimParticle_h
#include <Eigen/Dense>
#include <iostream>


namespace nbsim
{
  class Particle{

    public:
    Particle();
    Particle(const Eigen::Vector3d &position, const Eigen::Vector3d &velocity);
    ~Particle();

    public:
    // get the current position of the object
    Eigen::Vector3d getPosition();

    // get the current velocity of the object
    Eigen::Vector3d getVelocity();

    // update the position and velocity after a timestep
    void integrateTimestep(const Eigen::Vector3d &acceleration, const double &timestep);

    // get name of the particle
    std::string getName();

    // set name of the particle
    void setName(const std::string &name);

    // set the current position of the object
    void setPosition(const Eigen::Vector3d &position);

    // set the current velocity of the object
    void setVelocity(const Eigen::Vector3d &velocity);

    protected:
    Eigen::Vector3d m_position;
    Eigen::Vector3d m_velocity;
    std::string m_name = "undefined";

  };

} // end namespace

#endif
