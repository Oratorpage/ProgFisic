#include "conductor.hpp"

// In conductor devo racchiudere tutto e solamente quello che è necessario al
// far cooperare ed unire render e simulazione in maniera da farli lavorare in
// modo coeso e sensato

namespace bs {

Conductor::Conductor(Config const& configuration, double time_factor)
    : con_{configuration},
      sim_{configuration.wp, configuration.bp, configuration.sp},
      ren_{configuration.rp, configuration.bp},
      time_factor_{time_factor} {
  conInvariant();
}

void Conductor::conInvariant() {
  if (time_factor_ <= 0) {
    throw std::invalid_argument{
        "time_factor value is not acceptable, cannot be less or equal to "
        "zero"};
  }
}

void Conductor::start() {
  sf::Clock clock;
  double time_buffer{};

  while (ren_.isFWOpen()) {
    ren_.manageEvents();
    // sim_.uniteViewStats(ren_.getViewStats(sim_.currentFlock()));
    ren_.renderFrame(sim_);

    double elapsed = clock.restart().asSeconds();
    time_buffer += elapsed * time_factor_;
    while (time_buffer >= sim_.deltaTime()) {
      sim_.tick();
      time_buffer -= sim_.deltaTime();
    }
  }
}

}  // namespace bs