#include <algorithm>
#include <cmath>
#include <random>

#include "functions.hpp"

////////////////////////////////////////////////////
/////            free functions               //////
////////////////////////////////////////////////////
std::random_device rd;
std::default_random_engine engine(rd());

bool spawn(int const rate) {                        //decides whether a road should spawn a car
  std::uniform_int_distribution<int> unif(1, 1000);
  int const test = unif(engine);
  if (test <= rate) {
    return true;
  }
  return false;
}

int random_call(int const max_exit, int const mean) {   //extract a random exit
  std::uniform_int_distribution<int> unif(1,max_exit);
  int assigned_exit = unif(engine);
  while ((assigned_exit > max_exit) || (assigned_exit == 0)) {
    assigned_exit = unif(engine);
  }
  return assigned_exit;
}

double module360(double angle) {              //equivalent to mod360
  while (angle >= 0.) {
    angle = angle - 2 * M_PI;
  }
  return angle + 2 * M_PI;
}

bool is_free(double const street_angle, rbout& roundabout,    //check if there's space in the rbout for a car to enter
             double const min_ang, double const offset) {
  auto it = std::find_if(
      roundabout.carrbout().begin(), roundabout.carrbout().end(), [&](car& c) {
        return ((std::abs(std::abs(street_angle + offset - module360((c).theta())) *180 / M_PI) < min_ang) || (std::abs(std::abs(street_angle + offset - module360((c).theta())) * 180 / M_PI) > (360. - min_ang)));});
  if (it != roundabout.carrbout().end()) {
    return false;
  } else {
    return true;
  }
}


bool myfunction(car const& c1, car const& c2) {    
  return module360(c2.theta()) > module360(c1.theta());
}


double distance_from_road(car const& c, std::vector<road>const& roads) {   
  if (module360(c.theta()) < roads[c.exit()-1].angle()) {
    return (-module360(c.theta()) + roads[c.exit()-1].angle());
  } else {
    double diff1 = std::abs(2*M_PI - module360(c.theta()));
    return (diff1 + roads[c.exit()-1].angle());
  }
}

double distance_from_car(car const& c1, car const& c2) {
  if (module360(c1.theta()) < module360(c2.theta())) {
    return (module360(c2.theta())-module360(c1.theta()));
  } else {
    double diff1 = std::abs(2*M_PI-module360(c1.theta()));
    return (diff1 + module360(c2.theta()));
  }
}

int to_int(double a) {
  double a_i = a;
  while (a> 0) {
    a = a-1;
  }
  a = a+1;
  return (a_i - a);
}

/////////////////////////////////////////
///////      car functions        ////////
/////////////////////////////////////////

double car::theta() const { return theta_; }
double car::t() const { return t_; }
double car::exit() const { return exit_; }
bool car::can_I_enter() const { return can_I_enter_; }
void car::can_I_enter_Y() { can_I_enter_ = true; }
void car::evolve_tplus(double v) { t_ += 0.01*v; }
void car::evolve_tminus(double v) { t_ -= 0.01*v; }
void car::evolve_ang(double v) { theta_ += 0.0075*v; }

////////////////////////////////////////
//////    rbout functions   ///////////
////////////////////////////////////////

int rbout::n_roads() const { return n_roads_; }
double rbout::rad() const { return radius_; }
std::vector<car>& rbout::carrbout() { return car_rbout; }
std::size_t rbout::size_rbout() const { return car_rbout.size(); }
bool rbout::empty_rbout() const { return car_rbout.empty(); }

void rbout::newcar_rbt(double const street_angle, int const mean, double offset) {
  car C = car(street_angle + offset, 0., random_call(n_roads(), mean), true);
  car_rbout.push_back(C);
}

void rbout::erase_rbt(std::vector<road> roads, double offset) {
  car_rbout.erase(
      std::remove_if(car_rbout.begin(), car_rbout.end(),
                     [=](car& c) {
                       return module360(std::abs(c.theta() -roads[c.exit() - 1].angle() + offset)) < 0.05;
                     }),
      car_rbout.end());
}

int rbout::transfer_rbt(std::vector<road> roads, const double offset) {
  auto it = std::find_if(car_rbout.begin(), car_rbout.end(), [&](car& c) {
    return module360(std::abs(c.theta() - roads[c.exit() - 1].angle() +
                              offset)) < 0.05;
  });
  if (it == car_rbout.end()) {
    return 0;
  } else {
    return it->exit();
  }
}

void rbout::evolve_rbt(std::vector<road> roads, double v_rbout) {
  if (car_rbout.size() != 1) {
    for (auto it = car_rbout.begin(); it != car_rbout.end(); ++it) {
      std::sort(car_rbout.begin(),car_rbout.end(),myfunction);
      double const angle_difference = distance_from_road(*it,roads);
      if (std::abs(module360(angle_difference)) >= 0.05) {  //
        if (it != car_rbout.end()-1) {
          it->evolve_ang(v_rbout);
        } else {
          it->evolve_ang(v_rbout);
        }
      }
    }
  }
  if (car_rbout.size() == 1) {
    double const angle_difference = distance_from_road(car_rbout[0],roads);
    if (std::abs(module360(angle_difference)) >= 0.05) {
      car_rbout[0].evolve_ang(v_rbout);
    }
  }
}

///////////////////////////////////////
//////      road functions      ////////
///////////////////////////////////////

double road::angle() const { return angle_; }
double road::rate() const {return rate_;}
std::vector<car>& road::carin() { return car_in; }
std::vector<car>& road::carout() { return car_out; }
std::size_t road::size_in() const { return car_in.size(); }
std::size_t road::size_out() const { return car_out.size(); }
bool road::empty_in() const { return car_in.empty(); }
bool road::empty_out() const { return car_out.empty(); }

void road::newcar_rd(bool const input, int rate, int const n_max, const double offset) {
  if (input) {
    if ((static_cast<int>(size_in()) < n_max) && (spawn(rate))) {
      car C = car(0., 0., 0, false);
      car_in.push_back(C);
    }
  } else {
    car C_ = car(angle() - offset, 1., 0, true);
    car_out.push_back(C_);
  }
}

void road::evolve_rd(bool const input, rbout& roundabout, double const min_ang,
                     double v_road, double dist_from_rbout, double min_dist, double const offset, double const amp) {
  if (input) {
    for (int i = 0; i < static_cast<int>(size_in()); i++) {
      if (i==0){
        if((car_in[i]).t() < dist_from_rbout){
            car_in[i].evolve_tplus(v_road);
        } else {
          if((is_free(angle(), roundabout, min_ang, offset))&&(!car_in[i].can_I_enter())){
            car_in[i].evolve_tplus(v_road);
            car_in[i].can_I_enter_Y();
          }
        }
      }
      if (car_in[i].can_I_enter()) {
        car_in[i].evolve_tplus(amp*v_road);
      }
      if ((i != 0) && ((car_in[i]).t() < dist_from_rbout) &&
          (std::abs((car_in[i]).t() - (car_in[i - 1]).t()) > min_dist)) {
        car_in[i].evolve_tplus(v_road);
      }
    }
  } else {
    for (int i = 0; i < static_cast<int>(size_out()); i++) {
      if ((car_out[i]).t() > 0.) {
        car_out[i].evolve_tminus(v_road);
      }
    }
  }
}

bool road::transfer_rd() {
  auto it = std::find_if(car_in.begin(), car_in.end(),
                         [](car& car) { return car.t() >= 1; });
  if (it != car_in.end()) {
    car_in.erase(it);
    return true;
  } else {
    return false;
  }
}

void road::erase_rd() {
  auto it = std::find_if(car_out.begin(), car_out.end(),
                         [](car& car) { return car.t() <= 0; });
  if (it != car_out.end()) {
    car_out.erase(it);
  }
}
