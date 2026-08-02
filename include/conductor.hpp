#ifndef BS_CONDUCTOR_HPP
#define BS_CONDUCTOR_HPP

#include "config.hpp"
#include "render.hpp"
#include "simulation.hpp"

// The conductor manages the simulation and the render, it' the top layer

namespace bs {

class Conductor {
 private:
  Config con_;

  Simulation sim_;
  Render ren_;

  double time_factor_{1.0};

  void conInvariant();

 public:
  Conductor(Config const& configuration,
            double time_factor);

  void start();
};
}  // namespace bs

#endif