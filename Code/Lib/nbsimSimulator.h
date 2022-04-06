#ifndef nbsimSimulator_h
#define nbsimSimulator_h
#include "nbsimMassiveParticle.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <Eigen/Dense>


namespace nbsim{

    class Simulator{ // define an abtract simulator class to achieve polymorphism of generator

        public:
        Simulator(){};
        ~Simulator(){};

        public:

        // generate planet set, add all other MassiveParticle bodies to their list of attractors
        virtual void Generator() = 0;

        // print start position and energy
        virtual void printIniSummary() = 0;

        // act simulation
        void beginSimulation();

        // calculate Energy after the simulation
        void calculateEnergy();

        // print positions of the planets at the end of the simulation
        void printEndPosition();

        // print energies of the planets at the end of the simulation
        void printEndEnergy();
        
        protected:
        std::vector<std::shared_ptr<nbsim::MassiveParticle>> planet_set;
        double m_timestep;
        double m_timelength;
        double m_Energy_total;
        double m_Energy_kinetic;
        double m_Energy_potential;

    };
}

#endif