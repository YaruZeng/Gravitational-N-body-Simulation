#ifndef nbsimSolarSystem_h
#define nbsimSolarSystem_h
#include "nbsimSimulator.h"

namespace nbsim{

    class SolarSystem: public nbsim::Simulator{

        public:
        SolarSystem(const double &timestep, const double &timelength);
        ~SolarSystem(){};
        virtual void Generator();
        void printIniSummary();

        private:
        std::vector<double> m_beginEnergy={0,0,0};


    };

} 


#endif