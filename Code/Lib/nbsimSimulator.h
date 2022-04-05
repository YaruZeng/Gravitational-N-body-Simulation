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
        void printResult();
        
        protected:
        std::vector<std::shared_ptr<nbsim::MassiveParticle>> planet_set;
        double m_timestep;
        double m_timelength;
        std::vector<double> m_endEnergy={0,0,0};
        

    };
}

#endif