#ifndef nbsimSimulator_h
#define nbsimSimulator_h
#include "nbsimMassiveParticle.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <Eigen/Dense>


namespace nbsim{

    class Simulator{

        public:
        Simulator(){};
        ~Simulator(){};
        virtual void Generator() = 0;
        virtual void printIniSummary() = 0;
        void beginSimulation();
        void calculateEnergy();
        void printEndPosition();
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