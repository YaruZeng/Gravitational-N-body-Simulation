#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include <iostream>
#include <vector>
#include <cmath>


TEST_CASE("Particle Test1", "[a = 0]" ) {

  //Test for x = 0, v and timestep are int

  Eigen::Vector3d x1(0,0,0);
  Eigen::Vector3d v1(1,1,1);
  nbsim::Particle particle1(x1,v1);

  Eigen::Vector3d acceleration1(0,0,0);
  double timestep1 = 1;
  particle1.integrateTimestep(acceleration1, timestep1);

  Eigen::Vector3d expect_x1(1,1,1);
  Eigen::Vector3d expect_v1(1,1,1);
  REQUIRE(particle1.getPosition() == expect_x1);
  REQUIRE(particle1.getVelocity() == expect_v1);

  //Test for v = 0, x and timestep are float

  Eigen::Vector3d x2(0.1,0.1,0.2);
  Eigen::Vector3d v2(0,0,0);
  nbsim::Particle particle2(x2,v2);

  Eigen::Vector3d acceleration2(0,0,0);
  double timestep2 = 0.5;
  particle2.integrateTimestep(acceleration2, timestep2);

  Eigen::Vector3d expect_x2(0.1,0.1,0.2);
  Eigen::Vector3d expect_v2(0,0,0);
  REQUIRE(particle2.getPosition() == expect_x2);
  REQUIRE(particle2.getVelocity() == expect_v2);

  //Test for v = 0 and x = 0, timestep is int

  Eigen::Vector3d x3(0,0,0);
  Eigen::Vector3d v3(0,0,0);
  nbsim::Particle particle3(x3,v3);

  Eigen::Vector3d acceleration3(0,0,0);
  double timestep3 = 10;
  particle3.integrateTimestep(acceleration3, timestep3);

  Eigen::Vector3d expect_x3(0,0,0);
  Eigen::Vector3d expect_v3(0,0,0);
  REQUIRE(particle3.getPosition() == expect_x3);
  REQUIRE(particle3.getVelocity() == expect_v3);

  //Test for float, zero and minus input values

  Eigen::Vector3d x4(0.1,0.2,-0.3);
  Eigen::Vector3d v4(0.2,0,-3);
  nbsim::Particle particle4(x4,v4);

  Eigen::Vector3d acceleration4(-3,1.5,0);
  double timestep4 = 0.5;
  particle4.integrateTimestep(acceleration4, timestep4);

  Eigen::Vector3d expect_x4(0.2,0.2,-1.8);
  Eigen::Vector3d expect_v4(-1.3,0.75,-3);
  REQUIRE(particle4.getPosition() == expect_x4);
  REQUIRE(particle4.getVelocity() == expect_v4);

}


TEST_CASE("Particle Test2", "[a = constant]" ) {

  // Test for a is int
  
  Eigen::Vector3d x1(0,0,0);
  Eigen::Vector3d v1(1,1,1);
  nbsim::Particle particle1(x1,v1);

  Eigen::Vector3d acceleration1(0,2,1);
  double timestep1 = 2;
  particle1.integrateTimestep(acceleration1, timestep1);

  Eigen::Vector3d expect_x1(2,2,2);
  Eigen::Vector3d expect_v1(1,5,3);
  REQUIRE(particle1.getPosition() == expect_x1);
  REQUIRE(particle1.getVelocity() == expect_v1);

  // Test for a is float

  Eigen::Vector3d x2(-0.5,5,0);
  Eigen::Vector3d v2(0.1,0.1,1);
  nbsim::Particle particle2(x2,v2);

  Eigen::Vector3d acceleration2(0.5,0.5,0.2);
  double timestep2 = 2;
  particle2.integrateTimestep(acceleration2, timestep2);

  Eigen::Vector3d expect_x2(-0.3,5.2,2);
  Eigen::Vector3d expect_v2(1.1,1.1,1.4);
  REQUIRE(particle2.getPosition() == expect_x2);
  REQUIRE(particle2.getVelocity() == expect_v2);

}


TEST_CASE("Particle Test3", "[a = -x(t)]" ) {

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


TEST_CASE( "MassiveParticle Test1", "[Linear motion]" ) {

  double mu1 = 1.0;
  Eigen::Vector3d x1(0,0,0);
  Eigen::Vector3d v1(1,1,1);
  nbsim::MassiveParticle mp1(x1,v1,mu1);

  double timestep1 = 1.0;

  for(int i = 0; i < 5; ++i){
    mp1.calculateAcceleration();
    mp1.integrateTimestep(timestep1);
    Eigen::Vector3d expect_v1(1,1,1);
    REQUIRE(mp1.getVelocity() == expect_v1);
  }

  Eigen::Vector3d expect_x1(5,5,5);
  REQUIRE(mp1.getPosition() == expect_x1);

}


TEST_CASE( "MassiveParticle Test2", "[Motion of two bodies]" ) {

  // Initialize two bodies

  Eigen::Vector3d x1(1,0,0);
  Eigen::Vector3d v1(0,0.5,0);
  std::shared_ptr<nbsim::MassiveParticle> mp1 = std::make_shared<nbsim::MassiveParticle>(x1, v1);

  Eigen::Vector3d x2(-1,0,0);
  Eigen::Vector3d v2(0,-0.5,0);
  std::shared_ptr<nbsim::MassiveParticle> mp2 = std::make_shared<nbsim::MassiveParticle>(x2, v2);

  // Set mu and attractors

  (*mp1).setMu(1.0);
  (*mp2).setMu(1.0);
  (*mp1).addAttractor(mp2);
  (*mp2).addAttractor(mp1);

  // take motion and test

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