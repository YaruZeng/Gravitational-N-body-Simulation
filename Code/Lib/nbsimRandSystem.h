#ifndef nbsimRandSystem_h
#define nbsimRandSystem_h
#include "nbsimSimulator.h"
#include <vector>
#include <iostream>

namespace nbsim{

    class RandSystem: public nbsim::Simulator{
        public:
        RandSystem(const double &timestep, const double &timelength, const int &num);
        ~RandSystem(){};
        virtual void Generator();
        virtual void printIniSummary();

        private:
        std::vector<double> m_beginEnergy={0,0};
        int m_particle_num = 0;

    };


}

#endif