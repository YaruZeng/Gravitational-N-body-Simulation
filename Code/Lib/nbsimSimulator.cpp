#include "nbsimSimulator.h"
#include <memory>
#include <array>


namespace nbsim {

    void Simulator::beginSimulation(){

        for (double time = 0; time < m_timelength; time += m_timestep){
            
            for (auto planet:planet_set){
                (*planet).calculateAcceleration();
            }

            for (auto planet:planet_set){
                (*planet).integrateTimestep(m_timestep);
            }
        }

    }

    void Simulator::calculateEnergy(){

        m_Energy_kinetic = 0;
        m_Energy_potential = 0;
        
        for (auto planetA : planet_set){

            m_Energy_kinetic += 0.5 * ((*planetA).getMu() * (*planetA).getVelocity().squaredNorm());

            for (auto planetB : planet_set){
                if ((*planetA).getName() != (*planetB).getName()){
                    m_Energy_potential += -0.5 * (*planetA).getMu() * (*planetB).getMu() / ((*planetA).getPosition() - (*planetB).getPosition()).norm();
                }
            }
        }
        m_Energy_total = m_Energy_kinetic + m_Energy_potential;

    }

    void Simulator::printEndPosition(){

        std::cout << "----------------- End Position -----------------" << "\n";
        std::cout << "\n";
        for (auto planet : planet_set){
            std::cout << (*planet).getName() << ": " << "(" << (*planet).getPosition()[0] << ", " << (*planet).getPosition()[1] << ", " << (*planet).getPosition()[2] << ")" << "\n";
        }
        std::cout << "\n";

    }

    void Simulator::printEndEnergy(){

        std::cout << "------------------ End Energy ------------------" << "\n";
        std::cout << "\n";
        std::cout << "Total Energy: " << m_Energy_total << "\n";
        std::cout << "Kinetic Energy: " << m_Energy_kinetic << "\n";
        std::cout << "Potential Energy: " << m_Energy_potential << "\n";
        std::cout << "\n";

    }

}