#ifndef nbsimRandSystemMP_h
#define nbsimRandSystemMP_h
#include "nbsimSimulatorMP.h"
#include <vector>
#include <iostream>

namespace nbsim{

    // use OpenMP to optimise the performance
    class RandSystemMP: public nbsim::SimulatorMP{
        
        public:
        RandSystemMP(const double &timestep, const double &timelength, const int &num);
        ~RandSystemMP(){};

        public:
        virtual void Generator();
        virtual void printIniSummary();

        private:
        std::vector<double> m_beginEnergy={0,0};
        int m_particle_num = 0;

    };


}

#endif