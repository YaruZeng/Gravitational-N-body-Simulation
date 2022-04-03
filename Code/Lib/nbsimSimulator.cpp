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

    void Simulator::printSummary(){

        std::cout << "---------------- Start Position ----------------" << "\n";
        std::cout << "\n";
        for (auto item : nbsim::solarSystemData){
            std::cout << item.name << ": " << "(" << item.position[0] << ", " << item.position[1] << ", " << item.position[2] << ")" << "\n";
            std::cout << "\n";
        }

        std::cout << "---------------- End Position ----------------" << "\n";
        std::cout << "\n";
        for (auto planet:planet_set){
            std::cout << (*planet).getName() << ": " << "(" << (*planet).getPosition()[0] <<  ", " << (*planet).getPosition()[1] << ", " << (*planet).getPosition()[2] << ")" << "\n";
            std::cout << "\n";
        }

    }

}