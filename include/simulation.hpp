#ifndef BS_SIMULATION_HPP
#define BS_SIMULATION_HPP

#include <SFML/Graphics.hpp>

#include "behaviour.hpp"
#include "boid.hpp"
#include "boidProperties.hpp"
#include "rand.hpp"
#include "simulationParams.hpp"
#include "statistics.hpp"
#include "world.hpp"
#include "worldParams.hpp"

namespace bs {
class Simulation {
 private:
  World world_;
  // Se si volesse fare una cosa che si conclude da solo dopo tot allora
  // bisognerebbe avere l'input del numero totali di step

  BoidProperties properties_;
  int total_boids_{};
  std::vector<Boid> flock_{};

  double dt_{};
  Statistics stats_{};

  void buildFlock(SimParams const& sp);

 public:
  // questo vuol dire che la simulazione inevitabilemente dipende dai parametri
  // del mondo che sto considerando, cambbia mondo cambia simulazione
  Simulation(SimParams const& sp, WorldParams const& wp);

  World const& currentWorld() const;
  BoidProperties const& boidProperties() const;
  std::vector<Boid> const& currentFlock() const;
  double const deltaTime() const;
  Statistics const& currentStatistics() const;

  void calculateStats(std::vector<Boid> const& flock);
  void tick();
};
}  // namespace bs

#endif