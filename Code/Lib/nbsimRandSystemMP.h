#ifndef nbsimRandSystemMP_h
#define nbsimRandSystemMP_h
#include "nbsimSimulatorMP.h"
#include <vector>
#include <iostream>

namespace nbsim{

    class RandSystemMP: public nbsim::SimulatorMP{
        public:
        RandSystemMP(const double &timestep, const double &timelength, const int &num);
        ~RandSystemMP(){};
        virtual void Generator();
        virtual void printIniSummary();

        private:
        std::vector<double> m_beginEnergy={0,0};
        int m_particle_num = 0;

    };


}

#endif