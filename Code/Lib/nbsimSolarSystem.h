#ifndef nbsimSolarSystem_h
#define nbsimSolarSystem_h
#include "nbsimSimulator.h"

namespace nbsim{

    // create a generator of the Simulator for Solar System
    class SolarSystem: public nbsim::Simulator{ 

        public:
        SolarSystem(const double &timestep, const double &timelength);
        ~SolarSystem(){};

        public:
        virtual void Generator();
        virtual void printIniSummary();

        private:
        std::vector<double> m_beginEnergy={0,0,0};


    };

} 


#endif