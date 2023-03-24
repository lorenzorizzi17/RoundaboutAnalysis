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
    int const fps = 60;
    //geometric constants
    const double radius = 0.2 * display_height;
    const double lenghtCar = 4*0.0991*radius;
    const double widthCar = 4*0.0416*radius;
    const double lenghtRoad = 1.2*radius;
    const double widthRoad = 0.8*radius ;
    const double widthRoundabout = 0.25*radius;
    const double x = 0.25;
    const double offset = std::atan(((0.3*widthRoad))/((radius+widthRoundabout-x*radius)));
    
    //simulation parameters
    int const N_ROADS = 4;
    const double rates[N_ROADS] = {8,8,8,8};  //calcola flusso di ingresso
    const double amplificationTransfer = 1.2;
    const double v_road = 3;
    const double v_rbout = 2.85;
    const double dist_from_rbout = (radius -lenghtCar)/radius;
    const double min_dist_road = 1.2*(lenghtCar/lenghtRoad);
    const double n_max_car = 100;
    const double minimum_angle_behind = 50;
    const double minimum_angle_ahead = 25;
//sumo

    rbout roundabout(N_ROADS, radius);
    std::ofstream myfile;
    std::ofstream myfile2;
    myfile.open("data.dat");
    myfile2.open("timeseries.dat");

    std::vector<road> roads;
    for (int k = 0; k < roundabout.n_roads(); k++) {
      road strada_test(2 * k * M_PI / roundabout.n_roads(), rates[k]);
      roads.push_back(strada_test);
    }
    if (roads.size() != N_ROADS) {
        throw std::runtime_error{"Modificare il numero di strade."};
    }

    double b =0;
    while (true) {
        for (auto it = roads.begin(); it != roads.end(); ++it) {
          std::sort(roundabout.carrbout().begin(),roundabout.carrbout().end(), myfunction);
          (*it).newcar_rd(true, it->rate(), n_max_car, offset);
          (*it).evolve_rd(true, roundabout, minimum_angle_ahead, minimum_angle_behind, v_road, dist_from_rbout, min_dist_road, offset, amplificationTransfer);
          if (it->transfer_rd()) {
            roundabout.newcar_rbt(it->angle(), offset);
          }
          it->erase_rd();
          if (roundabout.transfer_rbt(roads, offset) > 0) {
            auto a = roundabout.transfer_rbt(roads, offset);
            (roads[a - 1]).newcar_rd(false, 0, n_max_car, offset);
          }
          roundabout.erase_rbt(roads, offset);
          it->evolve_rd(false, roundabout, 0,0, v_road, dist_from_rbout, min_dist_road, offset, amplificationTransfer);
        }
        roundabout.evolve_rbt(roads, v_rbout);
        
        double mean{0};
        for (auto it = roads.begin(); it != roads.end(); it++)
        {
          //std::cerr << "Macchine nella strada a " << (it->angle())*180/M_PI << " gradi: " << (it->carin()).size() << '\n';
          mean += (it->carin()).size();
        }
        std::cerr << mean/N_ROADS<<'\n';
        myfile << ((mean/N_ROADS)) <<std::endl;
        myfile2 << b << " " << ((mean/N_ROADS)) << std::endl;
        b++;
      }
      myfile.close();
      myfile2.close();
    }
    catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
