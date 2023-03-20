#ifndef ROUNDABOUT_H
#define ROUNDABOUT_H

#include "rbout.hpp"

class road {
 private:
  double angle_;
  double rate_;
  std::vector<car> car_in;
  std::vector<car> car_out;

 public:
  road(double angle = 0., double rate=0.) : angle_{angle}, rate_{rate} {}
  double angle() const;
  double rate() const;
  std::vector<car>& carin();
  std::vector<car>& carout();
  std::size_t size_in() const;
  std::size_t size_out() const;
  bool empty_in() const;
  bool empty_out() const;
  void newcar_rd(bool const, int, const int, const double);
  void evolve_rd(bool const, rbout&, double const,double const, double, double, double, const double, const double);
  bool transfer_rd();
  void erase_rd();
};

#endif
