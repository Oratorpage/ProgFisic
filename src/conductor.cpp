#include "conductor.hpp"

namespace bs {

Conductor::Conductor(SimParams const& sp, double time_factor)
    : sim_{sp}, ren_{sp}, time_factor_{time_factor} {}

void Conductor::start(SimParams const& sp) {
  sf::Clock clock;
  double time_buffer{};

  while (ren_.isFWOpen()) {
    ren_.manageEvents();

    double elapsed = clock.restart().asSeconds();
    time_buffer += elapsed * time_factor_;
    while (time_buffer >= sim_.deltaTime()) {
      sim_.update();
      time_buffer -= sim_.deltaTime();
    }
    ren_.renderFrame(sim_.currentFlock(), sp);
  }
};

}  // namespace bs