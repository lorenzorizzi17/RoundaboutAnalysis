# A simple roundabout simulation

A C++ codebase that aims to simulate the behaviour of a simple 4-road roundabout. The goal of the simulation is to gain insights 
into the traffic flow dynamics and to study the critical conditions under which queues are formed. 

The user can freely modify various parameters of the simulation, such as the rate of spawning vehicles, their velocities or
the angle of _caution_, to get different scenarios every time. For every run, some .txt files are created to keep track of 
the number of vehicles at every instant on the roundabout and on the roads, ready to be studied offline.
With the help of the framework ROOT, one can analyze the condition that should be met for the queues to form, the mean number of cars on the roads, their mean standing time and more.


![Recording 2023-09-09 at 22 24 03](https://github.com/lorenzorizzi17/RoundaboutAnalysis/assets/102590961/be589bbe-5217-461d-b71d-651df605f64e)

_P.S.: The code in this repo is implemented via SFML library. The GIF up there come from the adaptation of the same code I've made in Unity_