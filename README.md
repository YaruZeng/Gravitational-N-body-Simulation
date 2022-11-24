PHAS0100Assignment2
------------------

[![Build Status](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2.svg?branch=master)](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2)
[![Build Status](https://ci.appveyor.com/api/projects/status/[APPVEYOR_ID]/branch/master)](https://ci.appveyor.com/project/[USERNAME]/PHAS0100Assignment2)


Purpose
-------

This project serves as a starting point for the PHAS0100 Assignment 2 Gravitational N-body Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects,
that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 

Further information on the specific project is left as an exercise for the student.


Credits
-------

This project is maintained by [Dr. Jim Dobson](https://www.ucl.ac.uk/physics-astronomy/people/dr-jim-dobson). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).


Build Instructions
------------------

If you want to test or use this project, it can be built by the following instructions. In Linux terms: 

```
mkdir PHAS0100Assignment2-build
cd PHAS0100Assignment2-build
cmake ..
make
```


Use instructions
----------------

After building, if you could find programs 'nbsimBasicTest', 'randSystemSimulator', 'solarSystemSimulator' under the directory of build/bin, you can now test the project or run the motion simulation of planets system as instructions following.

1. Run Tests:

```
cd PHAS0100Assignment2/build
./bin/nbsimBasicTest
```

2. Run Solar System Simulation:

-Check help messages:

```
cd PHAS0100Assignment2/build
./bin/solarSystemSimulator -h
```

-Run the simulation by specifying motion timestep and timelength:

```
cd PHAS0100Assignment2/build
./bin/solarSystemSimulator ts TIMESTEP tl TIMELENGTH
```


3. Run Random System Simulation:

-Check help messages:

```
cd PHAS0100Assignment2/build
./bin/randSystemSimulator -h
```

-Run the simulation by specifying motion timestep, timelength, and number of particles:

```
cd PHAS0100Assignment2/build
./bin/randSystemSimulator ts TIMESTEP tl TIMELENGTH num PARTICLE_NUMBER
```

-Run the simulation by specifying motion timestep, timelength, and number of particles  in OpenMP parallelisation:

```
cd PHAS0100Assignment2/build
./bin/randSystemSimulator ts TIMESTEP tl TIMELENGTH num PARTICLE_NUMBER -MP
```


Summary of Simulator Performance
----------------

### PartB 4

Summary of Energy with various timesteps and timelength 100:

| timestep | timelength | initial E_total | end E_total | initial E_kinetic | end E_kinetic | initial E_potential | end E_potential |
| :----- | :----- | :----- | :----- | :----- | :----- | :----- | :----- |
| 0.000274 | 100 | -0.169514 | -0.164355 | 0.187358 | 0.131274 | -0.356872 | -0.295629 |
| 0.001 | 100 | -0.169514 | -0.158243 | 0.187358 | 0124411 | -0.356872 | -0.282653 |
| 0.00274 | 100 | -0.169514 | -0.14788 | 0.187358 | 0.217378 | -0.356872 | -0.365259 |
| 0.01 | 100 | -0.169514 | -0.122886 | 0.187358 | 0.101263 | -0.356872 | -0.224148 |
| 0.0274 | 100 | -0.169514 | -0.0939721 | 0.187358 | 0.0718046 | -0.356872 | -0.165777 |
| 0.274 | 100 | -0.169514 | 0.000193071 | 0.187358 | 0.138992 | -0.356872 | -0.138799 |
| 0.5 | 100 | -0.169514 | 0.140695 | 0.187358 | 0.180913 | -0.356872 | -0.0402175 |
| 1 | 100 | -0.169514 | 0.632578 | 0.187358 | 0.648087 | -0.356872 | -0.0155082 |

When the timesteps are chosen from 0.000274 to 1, the total energy remains between -1 and 1, which satisfies the sensible condition. At timestep 0.000274, the total energy at the end of the simulation, namely -0.164355, is close to the initial total energy -0.169514 with two digits of accuracy.

However, as the timestep increases, the error becomes larger with the total end energy from a negative value to a positive value at the turning point of around 0.274. 


### PartB 5

Summary of runtime with various timesteps:

| timestep | timelength | CPU Time(ms) | Wall Lock Time(ms) |
| :----- | :----- | :----- | :----- |
| 0.000274 | 100 | 305997.52 | 306001.86 |
| 0.001 | 100 | 84301.47 | 84306.26 |
| 0.00274 | 100 | 30574.68 | 30575.02 |
| 0.01 | 100 | 8063.90 | 8064.25 |
| 0.0274 | 100 | 2969.86 | 2969.88 |
| 0.274 | 100 | 317.37 | 317.31 |
| 0.5 | 100 | 176.01 | 175.93 |
| 1 | 100 | 99.15 | 98.49 |

Among the timesteps I choose, the simulation with the smallest timestep has the longest runtime. As the timestep grows, the runtime decreases. I think 0.001 is a good timestep which balances the accuracy(-0.158243 vs -0.169514) and the runtime(84306.26ms, namely 84.3s) best. 


### PartB 7

Summary of runtime in OpenMP with various thread numbers:

Simulation conditions: timestep = 0.000274, timelegth = 0.001, number of particles = 2000.

By setting OpenMP parallelisation and changing the number of threats, I got the run time:

| thread | CPU Time(ms) | Wall Lock Time(ms) |
| :-----| :----- | :----- |
| no MP | 206208.63 | 210455.62 |
| 1 | 205489.63 | 205494.66 |
| 2 | 232618.18 | 120189.36 |
| 3 | 241092.84 | 85365.00 |
| 4 | 246086.61 | 69478.67 |
| 5 | 246906.38 | 69604.59 |
| 6 | 242983.66 | 70600.81 |
| 7 | 243238.91 | 69355.95 |
| 8 | 243557.71 | 68830.17 |

For the CPU runtime, the simulation runtime before parallelisation is close to that after parallelisation on 1 thread, but it increases slightly when the number of threads increments and remains at around 240000ms on 3 and more threads. 

For the Wall Lock runtime, the speedup grows as the thread number grows and remains at around 3.0 on 4 and more threads. If we incease the number of particles, the runtime might be sped up more on large thread numbers.

In conclusion, we can use OpenMP parallelisation to increase the performance of our codes on the condition of an appropriate thread number.
