#include "conductor.hpp"

namespace bs {

Conductor::Conductor(Config const& configuration /*, double time_factor*/)
    : con_{configuration},
      sim_{configuration.wp, configuration.bp, configuration.sp},
      ren_{configuration.rp, configuration.bp} /*,
       time_factor_{time_factor}*/
{
  /*conInvariant();*/
}

/*void Conductor::conInvariant() {
  if (time_factor_ <= 0) {
    throw std::invalid_argument{
        "time_factor value is not acceptable, cannot be less or equal to "
        "zero"};
  }
}*/

// Starts the conductor which starts the render and simulation, it coordinates
// them
void Conductor::start(RenParams const& rp) {
  sf::Clock clock;
  ren_.setWindowsPosition(rp);

  while (ren_.isFWOpen()) {
    ren_.manageEvents();

    sim_.tick();

    ren_.renderFrame(sim_);
  }
}

}  // namespace bs