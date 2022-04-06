#include "nbsimRandSystemMP.h"
#include <memory>
#include <random>
#include <string>
#include <cmath>

namespace nbsim{

    RandSystemMP::RandSystemMP(const double &timestep, const double &timelength, const int &num){
        m_timestep = timestep;
        m_timelength = timelength;
        m_particle_num = num;

    }

    void RandSystemMP::Generator(){
        
        std::uniform_real_distribution<double> uniform_real_pos(0.4, 40);
        std::mt19937_64 mt64;
        auto ran_pos = std::bind(uniform_real_pos, mt64);

        double r,rx,ry,vx,vy,mu;

        std::shared_ptr<nbsim::MassiveParticle> mp;

        for (int i = 0; i < m_particle_num; ++i){

            std::string name = std::to_string(i+1);

            if (i == 0){
                rx = 0;
                ry = 0;
                vx = 0;
                vy = 0;
                mu = 50;
            }
            else{
                int theta = rand() % (180+1);
                r = ran_pos();
                rx = r * sin(theta * M_PI / 180);
                ry = r * cos(theta * M_PI / 180);
                vx = (-1 / std::sqrt(r)) * cos(theta * M_PI / 180);
                vy = (1 / std::sqrt(r)) * sin(theta * M_PI / 180);
                mu = 0.000001 + 1.0 * rand() / RAND_MAX * (0.005 - 0.000001);
            }

            mp = std::make_shared<nbsim::MassiveParticle>(name, Eigen::Vector3d(rx,ry,0), Eigen::Vector3d(vx,vy,0), mu);
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

    void RandSystemMP::printIniSummary(){

        double ini_E_kinetic = 0;
        double ini_E_potential = 0;
        double ini_E_total = 0;

        #pragma omp parallel for reduction(+:ini_E_kinetic, ini_E_potential)
        for (auto planetA : planet_set){

            ini_E_kinetic += 0.5 * ((*planetA).getMu() * (*planetA).getVelocity().squaredNorm());

            for (auto planetB : planet_set){
                if ((*planetA).getName() != (*planetB).getName()){
                    ini_E_potential += -0.5 * (*planetA).getMu() * (*planetB).getMu() / ((*planetA).getPosition() - (*planetB).getPosition()).norm();
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
        std::cout << "Kinetic Energy: " << m_beginEnergy[1] << "\n";
        std::cout << "Potential Energy: " << m_beginEnergy[2] << "\n";
        std::cout << "\n";

    }


}