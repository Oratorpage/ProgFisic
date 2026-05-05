//Defines the parameters that will be used
#ifndef FLOCK_SIMPARAMS_HPP
#define FLOCK_SIMPARAMS_HPP

namespace flock {

struct SimParams {
  int non_pred_boidnum{0};
  int pred_boidnum{0};
  double s{0.};
  double a{0.};
  double c{0.};
  double detection_rad{0.};
  double danger_rad{0.};
  bool toroidal{false};
  bool op_rad{false};
};

}  // namespace flock

#endif