#ifndef BS_SIMULATION_HPP
#define BS_SIMULATION_HPP

#include <SFML/Graphics.hpp>

#include "behaviour.hpp"
#include "boid.hpp"
#include "rand.hpp"
#include "simulationParams.hpp"
#include "statistics.hpp"

namespace bs {
class Simulation {
 private:
  // Se si volesse fare una cosa che si conclude da solo dopo tot allora
  // bisognerebbe avere l'input del numero totali di step
  int current_step_{0};
  int total_boids_{};
  std::vector<Boid> flock_{};

  double dt_{};
  Statistics stats_{};

  void buildFlock(SimParams const& sp);
  void calculateStats(std::vector<Boid> const& flock);

 public:
  Simulation(SimParams const& sp);

  int const currentStep() const;
  double const deltaTime() const;
  std::vector<Boid> const currentFlock() const;
};
}  // namespace bs

#endif