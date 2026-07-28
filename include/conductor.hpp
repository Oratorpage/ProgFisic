#ifndef BS_CONDUCTOR_HPP
#define BS_CONDUCTOR_HPP

#include "render.hpp"
#include "simulation.hpp"
#include "simulationParams.hpp"

// The conductor manages the simulation and the render, it' the top layer

namespace bs {

class Conductor {
 private:
  Simulation sim_;
  Render ren_;
  double time_factor_{};
  sf::RenderWindow flock_window_{};
  sf::RenderWindow statistics_window{};

 public:
  Conductor(SimParams const& sp, double time_factor);

  void start(SimParams const& sp);
};
}  // namespace bs

#endif