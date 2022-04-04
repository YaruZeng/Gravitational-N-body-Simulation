#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "nbsimSimulator.h"



static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "\t-h, --help\t\t\tShow this help message\n"
              << "Run the Solar System Simulator: \n"
              << "\tts, timestep TIMESTEP\t\tSpecify the timestep size of the motion\n"
              << "\ttl, timelength TIMELENGTH\tSpecify the length of motion time"
              << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 5) {
        show_usage(argv[0]);
        return 0;
    }

    double timestep = 0;
    double timelength = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } 
        else if ((arg == "ts") || (arg == "timestep")) {
            timestep = atof(argv[++i]); 
        } 
        else if ((arg == "tl") || (arg == "timelength")) {
            timelength = atof(argv[++i]); 
        }

    }

    nbsim::Simulator simulator(timestep, timelength);
    simulator.generatePlanetSet();
    simulator.beginSimulation();
    simulator.printSummary();

    return 0;
}