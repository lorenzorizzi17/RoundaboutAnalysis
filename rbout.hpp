#ifndef RBOUT_H
#define RBOUT_H

#include <stdexcept>
#include <vector>

#include "car.hpp"
class road;

class rbout {
 private:
  int n_roads_;
  double radius_;
  std::vector<car> car_rbout;

 public:
  rbout(int n_roads = 0, double rad = 0.) : n_roads_{n_roads}, radius_{rad} {
    if (n_roads_ <= 0) {
      throw std::runtime_error{"Il numero di strade deve essere maggiore di zero"};
    }
  }
  int n_roads() const;
  double rad() const;
  std::vector<car>& carrbout();
  std::size_t size_rbout() const;
  bool empty_rbout() const;
  void newcar_rbt(double const, const double, int);
  void erase_rbt(std::vector<road>, const double);
  int transfer_rbt(std::vector<road>, const double);
  void evolve_rbt(std::vector<road>, double);
};

#endif
