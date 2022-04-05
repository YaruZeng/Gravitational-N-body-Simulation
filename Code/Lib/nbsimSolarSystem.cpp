#include "nbsimSolarSystem.h"
#include "nbsimSolarSystemData.ipp"

namespace nbsim {

    SolarSystem::SolarSystem(const double &timestep, const double &timelength){
        m_timestep = timestep;
        m_timelength = timelength;

    }

    void SolarSystem::Generator(){

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

    void SolarSystem::printIniSummary(){

        double ini_E_kinetic = 0;
        double ini_E_potential = 0;
        double ini_E_total = 0;

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

        std::cout << "----------------- Start Energy -----------------" << "\n";
        std::cout << "\n";
        std::cout << "Total Energy: " << m_beginEnergy[0] << "\n";
        std::cout << "\n";
        std::cout << "Kinetic Energy: " << m_beginEnergy[1] << "\n";
        std::cout << "\n";
        std::cout << "Potential Energy: " << m_beginEnergy[2] << "\n";
        std::cout << "\n";

        std::cout << "---------------- Start Position ----------------" << "\n";
        std::cout << "\n";
        for (auto item : nbsim::solarSystemData){
            std::cout << item.name << ": " << "(" << item.position[0] << ", " << item.position[1] << ", " << item.position[2] << ")" << "\n";
            std::cout << "\n";
        }
    }
}