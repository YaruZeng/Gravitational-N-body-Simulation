#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include <iostream>
#include <vector>
#include <cmath>


TEST_CASE("Test of motion with a = 0", "[Particle]" ) {

  Eigen::Vector3d x(0,0,0);
  Eigen::Vector3d v(1,1,1);
  nbsim::Particle particle(x,v);

  Eigen::Vector3d acceleration(0,0,0);
  double timestep = 1;
  particle.integrateTimestep(acceleration, timestep);

  Eigen::Vector3d expect_x(1,1,1);
  Eigen::Vector3d expect_v(1,1,1);
  REQUIRE(particle.getPosition() == expect_x);
  REQUIRE(particle.getVelocity() == expect_v);

}


TEST_CASE("Test of motion with a = constant", "[Particle]" ) {

  Eigen::Vector3d x(0,0,0);
  Eigen::Vector3d v(1,1,1);
  nbsim::Particle particle(x,v);

  Eigen::Vector3d acceleration(0,2,1);
  double timestep = 2;
  particle.integrateTimestep(acceleration, timestep);

  Eigen::Vector3d expect_x(2,2,2);
  Eigen::Vector3d expect_v(1,5,3);
  REQUIRE(particle.getPosition() == expect_x);
  REQUIRE(particle.getVelocity() == expect_v);

}


TEST_CASE("Test of motion with a = -x(t)", "[Particle]" ) {

  Eigen::Vector3d x(1,0,0);
  Eigen::Vector3d v(0,1,0);
  nbsim::Particle particle(x,v);
  double timestep = 2*M_PI/2000;
  for (int i = 0; i < 2000; ++i)
  {
    Eigen::Vector3d acceleration = -particle.getPosition();
    particle.integrateTimestep(acceleration, timestep);
  }

  Eigen::Vector3d expect_x(1,0,0);
  Eigen::Vector3d expect_v(0,1,0);
  REQUIRE(expect_x.isApprox(particle.getPosition(), 0.01));
  REQUIRE(expect_v.isApprox(particle.getVelocity(), 0.01));
  
}


TEST_CASE( "Test of linear motion", "[MassiveParticle]" ) {

  double mu = 1.0;
  Eigen::Vector3d x(0,0,0);
  Eigen::Vector3d v(1,1,1);
  nbsim::MassiveParticle mp(x,v,mu);

  double timestep = 1.0;

  for(int i = 0; i < 5; ++i){
    mp.calculateAcceleration();
    mp.integrateTimestep(timestep);
    Eigen::Vector3d expect_v(1,1,1);
    REQUIRE(mp.getVelocity() == expect_v);
  }

  Eigen::Vector3d expect_x(5,5,5);
  REQUIRE(mp.getPosition() == expect_x);

}


TEST_CASE( "Motion of two bodies", "[MassiveParticle]" ) {

  Eigen::Vector3d x1(1,0,0);
  Eigen::Vector3d v1(0,0.5,0);
  std::shared_ptr<nbsim::MassiveParticle> mp1 = std::make_shared<nbsim::MassiveParticle>(x1, v1);

  Eigen::Vector3d x2(-1,0,0);
  Eigen::Vector3d v2(0,-0.5,0);
  std::shared_ptr<nbsim::MassiveParticle> mp2 = std::make_shared<nbsim::MassiveParticle>(x2, v2);

  (*mp1).setMu(1.0);
  (*mp2).setMu(1.0);
  (*mp1).addAttractor(mp2);
  (*mp2).addAttractor(mp1);

  double timestep = 2*M_PI/2000;
  double ini_dist = std::sqrt(((*mp1).getPosition()-(*mp2).getPosition()).cwiseAbs2().sum());
  std::vector<double> diff = {(ini_dist-2)};

  for (int i = 0; i < 2000; ++i){
    
    (*mp1).calculateAcceleration();
    (*mp2).calculateAcceleration();
    (*mp1).integrateTimestep(timestep);
    (*mp2).integrateTimestep(timestep);
    double tmp_dist = 0.0;
    tmp_dist = std::sqrt(((*mp1).getPosition()-(*mp2).getPosition()).cwiseAbs2().sum());
    diff.push_back(std::abs(tmp_dist - 2));

  }

  double max_diff = *max_element(diff.begin(),diff.end()); 
  REQUIRE(max_diff < 0.02);

}