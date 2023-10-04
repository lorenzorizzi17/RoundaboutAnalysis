# A simple roundabout simulation

A C++ codebase that aims to simulate the behaviour of a simple 4-road roundabout. The goal of the simulation is to gain insights 
into the traffic flow dynamics and to study the critical conditions under which queues are formed. 

The user can freely modify various parameters of the simulation, such as the rate of spawning vehicles, their velocities or
the angle of _caution_, to get different scenarios every time. For every run, some .txt files are created to keep track of 
the number of vehicles at every instant on the roundabout and on the roads, ready to be studied offline.
With the help of the framework ROOT, one can analyze the condition that should be met for the queues to form, the mean number of cars on the roads, their mean standing time and more.


![Recording 2023-09-09 at 22 24 03](https://github.com/lorenzorizzi17/RoundaboutAnalysis/assets/102590961/be589bbe-5217-461d-b71d-651df605f64e)

_P.S.: The code in this repo is implemented via SFML library. The GIF up there comes from the adaptation of the same code I've made in Unity_

## How to build and run the program (CMake)
To correctly compile and build the program, one can take advantage of the CMake software. Just enter the terminal and, in the general directory, type:

`$ cmake -DGRAPHIC=OFF -S ./source -B ./build `

The option `-DGRAPHIC` can be turned on to visualize graphically the roundabout simulation. Clearly, this will increase significantly the time needed at run-time for the simulation to store data. Therefore I highly suggest to set this variable off when only analysing different scenarios.

Once the CMake configuration has finished, build the code:

`$ cmake --build build`

This will automatically create in `/build` directory an executable file, `Roundaboutng.out` (or `Roundabout.out` if you set graphic mode on). To run the code, simply digit:

`$ build/Roundaboutng.out`

## How to analyze data
At every run, the program store in `/data` folder some .txt files (namely `data0.dat`, `data1.dat`, ...). These contain the number of cars in every road at every istant. The same structure caracterizes `time0.dat`, `times1.dat` files, but in this case the first column indicates the current time (in clock cycle).

To analyze these data, I created a ROOT macro (inside `/ROOT` directory). The macro contains two main functions, namely:
* timeseries(): plot number of cars vs time in a graph and print out the linear coefficient of the fitting line
* histo(): plot a histogram for every road evaluating the occurencies in the number of cars
