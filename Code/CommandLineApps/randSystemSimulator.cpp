#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "nbsimSimulator.h"
#include "nbsimSimulatorMP.h"
#include "nbsimRandSystem.h"
#include "nbsimRandSystemMP.h"
#include <ctime>
#include <iomanip>
#include <chrono>
#include <memory>
#include <omp.h>

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
              << "Options:\n"
              << "Get the Help Message: \n"
              << "\t-h, --help\t\t\tShow this help message\n"
              << "Run the Random System Simulator: \n"
              << "Compolsary: \n"
              << "\tts, timestep TIMESTEP\t\tSpecify the timestep size of the motion\n"
              << "\ttl, timelength TIMELENGTH\tSpecify the length of motion time\n"
              << "\tnum, particle_num NUMBER\tSpecify the number of random particles\n"
              << "Optional:\n"
              << "\t-MP, -openmp\t\tRun the simulator using OpenMP parallelization\n"
              << std::endl;
}

void Simulation(nbsim::Simulator &system){
    
    system.Generator();
    system.printIniSummary();
    system.beginSimulation();
    system.calculateEnergy();
    system.printEndEnergy();
    
}

void SimulationMP(nbsim::SimulatorMP &system){
    
    system.Generator();
    system.printIniSummary();
    system.beginSimulation();
    system.calculateEnergy();
    system.printEndEnergy();
    
}

int main(int argc, char* argv[])
{
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    if (argc < 7) {
        show_usage(argv[0]);
        return 0;
    }

    double timestep = 0;
    double timelength = 0;
    int openmp = 0;
    int particle_num = 0;

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
        else if ((arg == "num") || (arg == "particle_num")) {
            particle_num = atoi(argv[++i]); 
        }
        else if ((arg == "-MP") || (arg == "-openmp")) {
            openmp = 1; 
        } 

    }

    if (openmp == 0){
        nbsim::RandSystem random(timestep, timelength, particle_num);
        Simulation(random);
    }
    else
    {
        omp_set_num_threads (2);
        nbsim::RandSystemMP random(timestep, timelength, particle_num);
        SimulationMP(random);
    }


    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << "------------------------------------------------" << "\n";
    std::cout << "\n";

    std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";

    return 0;
}
