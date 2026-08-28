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
// Specialized class to manage a simulation of boids
class Simulation {
 private:
  World world_;
  // A total step number simulation could be done, even with a seed to achieve a
  // more replicable and standard result, to do that only the rand TU and the
  // simulation tick need to be changed (maybe also the render to improve it
  // casewise)(also the statistics, the step may be put there)

  BoidProperties boid_properties_;
  int total_boids_{};
  std::vector<Boid> flock_{};

  double dt_{};
  Statistics stats_;

  void buildFlock(SimParams const& sp, BoidProperties const& bp);
  void firstStats(std::vector<Boid> const& flock);
  void simInvariant();

 public:
  // The simulation necessarily depends on the world parameters where it is
  // being simulated, on the properties of what it is simulating and on the
  // parameters itself of the simulation
  Simulation(WorldParams const& wp, BoidProperties const& bp,
             SimParams const& sp);

  World const& currentWorld() const;
  BoidProperties const& boidProperties() const;
  std::vector<Boid> const& currentFlock() const;
  double getSimdt() const;
  Statistics const& currentStatistics() const;

  void calculateStats(std::vector<Boid> const& flock);
  // void uniteViewStats(std::string const& viewstats);
  void tick();
};
}  // namespace bs

#endif