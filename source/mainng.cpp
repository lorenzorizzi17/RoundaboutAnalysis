#include <string>

#include <cmath>
#include <iostream>
#include <fstream>
#include<algorithm>
#include "road.hpp"
#include "functions.hpp"
// per l'offset, ho che tan(alfa) = (0.5*widthRoad)/((radius+widthRoundabout-0.1*radius))
int main() {
  try {
    //graphic constants
    unsigned const display_height = 0.95 * 768;
    //int const fps = 60;
    //geometric constants
    const double radius = 0.2 * display_height;
    const double lenghtCar = 4*0.0991*radius;
    //const double widthCar = 4*0.0416*radius;
    const double lenghtRoad = 1.2*radius;
    const double widthRoad = 0.8*radius ;
    const double widthRoundabout = 0.25*radius;
    const double x = 0.25;
    const double offset = std::atan(((0.3*widthRoad))/((radius+widthRoundabout-x*radius)));
    
    //simulation parameters
    int const N_ROADS = 4;
    const double rates[N_ROADS] = {15,15,15,15};  //calcola flusso di ingresso
    const double amplificationTransfer = 1.2;
    const double v_road = 3;
    const double v_rbout = 2.85;
    const double dist_from_rbout = (radius -lenghtCar)/radius;
    const double min_dist_road = 1.2*(lenghtCar/lenghtRoad);
    const double n_max_car = 600;
    const double minimum_angle_behind = 50;
    const double minimum_angle_ahead = 25;
    const int n_cycle = 1E6;

    //file iostream managing
    std::ofstream roadsfile[N_ROADS];
    std::ofstream timesfile[N_ROADS];
    for(int i{0};i < N_ROADS;i++){
      std::string name = "/home/lorenzo17/Roundabout2/data/road" + std::to_string(i) + ".dat";
      roadsfile[i].open(name);
    }
    for(int i{0};i < N_ROADS;i++){
      std::string name = "/home/lorenzo17/Roundabout2/data/time" + std::to_string(i) + ".dat";
      timesfile[i].open(name);
    }

    //roundabout and roads creation
    rbout roundabout(N_ROADS, radius);
    std::vector<road> roads;
    for (int k = 0; k < roundabout.n_roads(); k++) {
      road strada_test(2 * k * M_PI / roundabout.n_roads(), rates[k]);
      roads.push_back(strada_test);
    }
    if (roads.size() != N_ROADS) {
        throw std::runtime_error{"Modificare il numero di strade."};
    }

    
    

    //manually modifying the initial n. of cars in a road
    /* for (int i = 0; i < 300; i++)
    {
      roads[0].newcar_rd(true,(RAND_MAX/1000),n_max_car,offset);
    } */
    
    int b = 0;
    while (b<n_cycle) {
        int number_current_road = 1;
        //making the calculation for every road
        for (auto it = roads.begin(); it != roads.end(); ++it) {
          it->newcar_rd(true, it->rate(), n_max_car, offset);
          it->evolve_rd(true, roundabout, minimum_angle_ahead, minimum_angle_behind, v_road, dist_from_rbout, min_dist_road, offset, amplificationTransfer);
          if (it->transfer_rd()) {
            roundabout.newcar_rbt(it->angle(), offset, number_current_road);
          }
          it->erase_rd();
          it->evolve_rd(false, roundabout, 0,0, v_road, dist_from_rbout, min_dist_road, offset, amplificationTransfer);
          roadsfile[number_current_road-1] << (it->carin()).size() << std::endl;
          timesfile[number_current_road-1] << b << " " << (it->carin()).size() << std::endl;
          number_current_road++;   
          //std::cerr << "Macchine nella strada a " << (it->angle())*180/M_PI << " gradi: " << (it->carin()).size() << '\n';     
        }
        //making the calculation for the roundabout
        if (roundabout.transfer_rbt(roads, offset) > 0) {
            int a = roundabout.transfer_rbt(roads, offset);
            (roads[a - 1]).newcar_rd(false, 0, n_max_car, offset);
          }
        roundabout.erase_rbt(roads, offset);
        roundabout.evolve_rbt(roads, v_rbout);
        
        //statistic part: computing the mean number of car
        /* double mean{0};
        for (auto it = roads.begin(); it != roads.end(); it++)
        {
          
          mean += (it->carin()).size();
        } */

        //updating the cycle and printing info
        b++;
        if (b%(n_cycle/100) ==0)
        {
          std::cerr << (b/(n_cycle/100)) << "\%" << '\n';
        }
      }
      
      
    
    //closing the file after the algorithm has finished
    for(int i=0;i < N_ROADS; i++){
        roadsfile[i].close();
    }
    for(int i=0;i < N_ROADS; i++){
        timesfile[i].close();
    }
      
      
    }
    catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
