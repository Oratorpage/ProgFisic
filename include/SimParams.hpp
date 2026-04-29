//Defines the parameters that will be used
#ifndef FLOCK_SIMPARAMS_HPP
#define FLOCK_SIMPARAMS_HPP

namespace flock {

struct SimParams {
  long unsigned int non_pred_boidnum{0};
  long unsigned int pred_boidnum{0};
  double s{0.};
  double a{0.};
  double c{0.};
  double detectrad{0.};
  double dangerrad{0.};
  bool toroidal{false};
  bool oprad{false};
};

}  // namespace flock

#endif