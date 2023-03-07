#include <string.h>

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "road.hpp"
#include "functions.hpp"


int main() {
    rbout roundabout(4, 4);

    const double radius = 0.25;
    const double lenghtCar = 2*0.0991*radius;
    const double lenghtRoad = 0.8*radius;
    const double v_max_road = 1.5;
    const double v_max_rbout = 1.5;
    const double dist_from_rbout = 0.75;
    const double min_dist_road = 1.25*lenghtCar/lenghtRoad;
    const double n_max_car = to_int(static_cast<double>(lenghtRoad/min_dist_road));

    std::vector<road> roads;
    for (int k = 0; k < roundabout.n_roads(); k++) {
      road strada_test(2 * k * M_PI / roundabout.n_roads());
      roads.push_back(strada_test);
    }
    
    car c = car(M_PI/2 -0.4,0,2,false);
    car c1 = car(M_PI/2 -0.1,0,2,false);
    std::cerr << n_max_car;




}