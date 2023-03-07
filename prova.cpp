bool is_free(double const street_angle, rbout& roundabout,
             double const min_ang) {
  for (int i{0}; i < static_cast<int>(roundabout.size_rbout()); i++) {
    double const angle_difference =
        std::abs(street_angle + offset -
                 module360(((roundabout.carrbout())[i]).theta()))*180/M_PI;
    double const a_d_degree = angle_difference * 180 / M_PI;
    if ((std::abs(a_d_degree) < min_ang) ||
        (std::abs(a_d_degree) > (360. - min_ang))) {
      return false;
    }
  }
  return true;
}

bool is_free(double const street_angle, rbout& roundabout,
             double const min_ang) {
  auto it = std::find_if(roundabout.carrbout().begin(),roundabout.carrbout().end(), [&] (car& c) {return ((std::abs(std::abs(street_angle + 0.offset
                 module360((c).theta()))*180/M_PI) < min_ang) ||
        (std::abs(std::abs(street_angle + offset -
                 module360((c).theta()))*180/M_PI) > (360. - min_ang)))});
  if (it!= car_rbout.end()) {
    return false;
  } else {return true;}
}
