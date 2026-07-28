#ifndef BS_SIMULATION_HPP
#define BS_SIMULATION_HPP

#include <SFML/Graphics.hpp>

#include "boid.hpp"
#include "simulationParams.hpp"
#include "behaviour.hpp"
#include "rand.hpp"

namespace bs {
class Simulation {
 private:
  // Se si volesse fare una cosa che si conclude da solo dopo tot allora
  // bisognerebbe avere l'input del numero totali di step
  int current_step_{0};
  int total_boids_{};
  std::vector<Boid> flock_{};

  double dt_{};

  void buildFlock(SimParams const& sp);

 public:
  Simulation(SimParams const& sp);

  int const Simulation::currentStep() const;
  double const deltaTime() const;
  std::vector<Boid> const Simulation::currentFlock() const;
  
};
}  // namespace bs

#endif