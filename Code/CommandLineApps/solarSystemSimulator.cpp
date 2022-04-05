#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "nbsimSimulator.h"
#include "nbsimSolarSystem.h"
#include <ctime>
#include <iomanip>
#include <chrono>
#include <memory>

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

void Simulation(nbsim::Simulator &system){
    
    system.Generator();
    system.printIniSummary();
    system.beginSimulation();
    system.calculateEnergy();
    system.printResult();
    
}

int main(int argc, char* argv[])
{
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

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

    nbsim::SolarSystem solar(timestep, timelength);
    Simulation(solar);

    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << "-------------------------------------------" << "\n";
    std::cout << "\n";

    std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";

    return 0;
}
