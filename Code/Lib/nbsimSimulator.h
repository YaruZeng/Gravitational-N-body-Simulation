#ifndef nbsimSimulator_h
#define nbsimSimulator_h
#include "nbsimMassiveParticle.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>


namespace nbsim{
    
    class Simulator{

        public:
        Simulator(const double &timestep, const double &timelength);
        ~Simulator();
        void generatePlanetSet();
        void beginSimulation();
        void printSummary();
        
        private:
        std::vector<std::shared_ptr<nbsim::MassiveParticle>> planet_set;
        double m_timestep;
        double m_timelength;
    
    };
}

#endif