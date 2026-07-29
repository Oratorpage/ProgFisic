#include "conductor.hpp"

namespace bs {

Conductor::Conductor(SimParams const& sp, double time_factor)
    : sim_{sp}, ren_{sp}, time_factor_{time_factor} {}

void Conductor::start(SimParams const& sp) {
  sf::Clock clock;
  double time_buffer{};
  // Questo mi piacerebbe in un qualche modo spostarlo dentro Render
  sf::ConvexShape non_pred_boid{makeBoidShape(sf::Color::Cyan)};
  sf::ConvexShape pred_boid{makeBoidShape(sf::Color::Red)};
  sf::CircleShape detection_circle{
      bs::makeCircleShape(sp.detection_rad, sf::Color::Green)};
  sf::CircleShape danger_circle{
      bs::makeCircleShape(sp.danger_rad, sf::Color::Red)};
  sf::CircleShape cm_circle{makeCenterDot()};
  //

  while (ren_.isFWOpen()) {
    ren_.manageEvents();

    double elapsed = clock.restart().asSeconds();
    time_buffer += elapsed * time_factor_;
    while (time_buffer >= sim_.deltaTime()) {
      sim_.update();
      time_buffer -= sim_.deltaTime();
    }

    ren_.renderFrame(sim_.currentFlock(), sp, non_pred_boid, pred_boid,
                     detection_circle, danger_circle, cm_circle);
  }
};

}  // namespace bs