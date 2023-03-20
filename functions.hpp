#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "road.hpp"

bool spawn(int const);

int random_call(int const, int const);

double module360(double);

bool is_free(double const, rbout &, double const, double const);

bool myfunction(car const&, car const&);

double distance_from_road(car const&, std::vector<road>const&);

double distance_from_car(car const&, car const&);

int to_int(double);

#endif