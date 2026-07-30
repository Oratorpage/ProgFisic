#include "conductor.hpp"

// In conductor devo racchiudere tutto e solamente quello che è necessario al
// far cooperare ed unire render e simulazione in maniera da farli lavorare in
// modo coeso e sensato

namespace bs {

Conductor::Conductor(Config const& configuration, double time_factor)
    : sim_{configuration.sp, configuration.wp}, ren_{configuration.rp}, time_factor_{time_factor} {}

void Conductor::start() {
  sf::Clock clock;
  double time_buffer{};

  while (ren_.isFWOpen()) {
    ren_.manageEvents();

    double elapsed = clock.restart().asSeconds();
    time_buffer += elapsed * time_factor_;
    while (time_buffer >= sim_.deltaTime()) {
      sim_.tick();
      time_buffer -= sim_.deltaTime();
    }
    sim_.calculateStats(sim_.currentFlock());
    ren_.renderFrame(sim_);
  }
}

}  // namespace bs