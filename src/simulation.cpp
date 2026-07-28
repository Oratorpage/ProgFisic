#include "simulation.hpp"

namespace bs {

void Simulation::buildFlock(SimParams const& sp) {
  flock_.reserve(static_cast<long unsigned int>(total_boids_));

  for (int i{0}; i < sp.non_pred_boidnum; ++i) {
    flock_.emplace_back(randVel(),
                        randPos({static_cast<double>(sp.flockWindowWidth),
                                 static_cast<double>(sp.flockWindowHeight)}));
  }
  for (int i{0}; i < sp.pred_boidnum; ++i) {
    flock_.emplace_back(randVel(),
                        randPos({static_cast<double>(sp.flockWindowWidth),
                                 static_cast<double>(sp.flockWindowHeight)}),
                        true);
  };
}

Simulation::Simulation(SimParams const& sp)
    : dt_{sp.dt}, total_boids_{sp.pred_boidnum + sp.non_pred_boidnum} {
  buildFlock(sp);
}

int const Simulation::currentStep() const { return current_step_; }
double const Simulation::deltaTime() const { return dt_; }
std::vector<Boid> const Simulation::currentFlock() const {
  return flock_;
}  // Il ritorno di questo vettore sarà un casino vero?

}  // namespace bs