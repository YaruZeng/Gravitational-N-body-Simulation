#include "nbsimSimulator.h"

namespace nbsim {

    void Simulator::beginSimulation(){

        for (double time = 0; time < m_timelength; time += m_timestep){
            // std::cout << "calculateAcceleration()" << "\n";
            for (auto planet:planet_set){
                (*planet).calculateAcceleration();
            }

            // std::cout << "integrateTimestep()" << "\n";
            for (auto planet:planet_set){
                (*planet).integrateTimestep(m_timestep);
            }
        }

    }

    void Simulator::calculateEnergy(){
        
        double end_E_kinetic = 0;
        double end_E_potential = 0;
        double end_E_total = 0;
        
        for (auto planetA : planet_set){

            end_E_kinetic += 0.5 * ((*planetA).getMu() * (*planetA).getVelocity().squaredNorm());

            for (auto planetB : planet_set){
                if ((*planetA).getName() != (*planetB).getName()){
                    end_E_potential += -0.5 * (*planetA).getMu() * (*planetB).getMu() / ((*planetA).getPosition() - (*planetB).getPosition()).norm();
                }
            }
        }
        
        end_E_total = end_E_kinetic + end_E_potential;
        m_endEnergy[0] = end_E_total;
        m_endEnergy[1] = end_E_kinetic;
        m_endEnergy[2] = end_E_potential;

    }

    void Simulator::printResult(){

        std::cout << "----------------- End Position -----------------" << "\n";
        std::cout << "\n";
        for (auto planet:planet_set){
            std::cout << (*planet).getName() << ": " << "(" << (*planet).getPosition()[0] <<  ", " << (*planet).getPosition()[1] << ", " << (*planet).getPosition()[2] << ")" << "\n";
            std::cout << "\n";
        }

        std::cout << "------------------ End Energy ------------------" << "\n";
        std::cout << "\n";
        std::cout << "Total Energy: " << m_endEnergy[0] << "\n";
        std::cout << "\n";
        std::cout << "Kinetic Energy: " << m_endEnergy[1] << "\n";
        std::cout << "\n";
        std::cout << "Potential Energy: " << m_endEnergy[2] << "\n";
        std::cout << "\n";

    }

}