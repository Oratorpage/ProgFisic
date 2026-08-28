#ifndef BS_SIMULATIONPARAMS_HPP
#define BS_SIMULATIONPARAMS_HPP

namespace bs {
// Parameters used to construct a simulation
struct SimParams {
  int non_pred_boidnum{10};
  int pred_boidnum{0};

  double dt{0.001};
};

}  // namespace bs

#endif