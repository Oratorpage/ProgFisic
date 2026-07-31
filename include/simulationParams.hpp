// Defines the parameters that will be used
#ifndef BS_SIMULATIONPARAMS_HPP
#define BS_SIMULATIONPARAMS_HPP

namespace bs {

struct SimParams {
  // Simulation
  int non_pred_boidnum{10};  
  int pred_boidnum{0};

  double dt{0.001};
};


}  // namespace bs

#endif