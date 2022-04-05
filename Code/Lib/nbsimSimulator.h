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
        Simulator(const double &timestep, const double &timelength);
        ~Simulator();
        void generatePlanetSet();
        void beginSimulation();
        void calculateEnergy();
        void printSummary();
        
        private:
        std::vector<std::shared_ptr<nbsim::MassiveParticle>> planet_set;
        double m_timestep;
        double m_timelength;
        // std::vector<Eigen::Vector3d> m_beginEnergy;
        // std::vector<Eigen::Vector3d> m_endEnergy;
        // std::array<Eigen::Vector3d,3> m_beginEnergy = {};
        // std::array<Eigen::Vector3d,3> m_endEnergy = {};
        std::vector<double> m_beginEnergy={0,0,0};
        std::vector<double> m_endEnergy={0,0,0};
    
    };
}

#endif