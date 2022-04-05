#include "nbsimSimulator.h"
#include "nbsimSolarSystemData.ipp"

namespace nbsim {

    Simulator::Simulator(const double &timestep, const double &timelength){
        m_timestep = timestep;
        m_timelength = timelength;
    }

    Simulator::~Simulator(){}

    void Simulator::generatePlanetSet(){

        std::shared_ptr<nbsim::MassiveParticle> mp;
    
        for (auto item:nbsim::solarSystemData){
            mp = std::make_shared<nbsim::MassiveParticle>(item.name, item.position, item.velocity, item.mu);
            planet_set.push_back(mp);
        }

        for (auto planetA:planet_set){
            for (auto planetB:planet_set){
                if ((*planetA).getName() != (*planetB).getName()){
                    (*planetA).addAttractor(planetB);
                } 
            }
        }
    }

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

        double ini_E_kinetic = 0;
        double ini_E_potential = 0;
        double ini_E_total = 0;
        
        double end_E_kinetic = 0;
        double end_E_potential = 0;
        double end_E_total = 0;

        for (auto itemA:nbsim::solarSystemData){

            ini_E_kinetic += 0.5 * (itemA.mu * (itemA.velocity).squaredNorm());

            for (auto itemB : nbsim::solarSystemData){
                if (itemA.name != itemB.name){
                    ini_E_potential += -0.5 * itemA.mu * itemB.mu / (itemA.position - itemB.position).norm();
                }
            }
        }

        ini_E_total = ini_E_kinetic + ini_E_potential;
        m_beginEnergy[0] = ini_E_total;
        m_beginEnergy[1] = ini_E_kinetic;
        m_beginEnergy[2] = ini_E_potential;

        
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

        std::cout << "----------------- Start Energy -----------------" << "\n";
        std::cout << "\n";
        std::cout << "Total Energy: " << m_beginEnergy[0] << "\n";
        std::cout << "\n";
        std::cout << "Kinetic Energy: " << m_beginEnergy[1] << "\n";
        std::cout << "\n";
        std::cout << "Potential Energy: " << m_beginEnergy[2] << "\n";
        std::cout << "\n";

    }

    void Simulator::printSummary(){

        std::cout << "---------------- Start Position ----------------" << "\n";
        std::cout << "\n";
        for (auto item : nbsim::solarSystemData){
            std::cout << item.name << ": " << "(" << item.position[0] << ", " << item.position[1] << ", " << item.position[2] << ")" << "\n";
            std::cout << "\n";
        }

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