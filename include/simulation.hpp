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

  BoidProperties boid_properties_;
  int total_boids_{};
  std::vector<Boid> flock_{};

  double dt_{};
  Statistics stats_;

  int tester_{0};

  void buildFlock(SimParams const& sp, BoidProperties const& bp);
  void firstStats(std::vector<Boid> const& flock);
  void simInvariant();

 public:
  // questo vuol dire che la simulazione inevitabilemente dipende dai parametri
  // del mondo che sto considerando, cambbia mondo cambia simulazione
  Simulation(WorldParams const& wp, BoidProperties const& bp,
             SimParams const& sp);

  World const& currentWorld() const;
  BoidProperties const& boidProperties() const;
  std::vector<Boid> const& currentFlock() const;
  double deltaTime() const;
  Statistics const& currentStatistics() const;

  void calculateStats(std::vector<Boid> const& flock);
  // void uniteViewStats(std::string const& viewstats);
  void tick();


  
};
}  // namespace bs

#endif