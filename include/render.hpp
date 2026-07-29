// Manages the render of the windows and the shapes
#ifndef BS_RENDER_HPP
#define BS_RENDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "boid.hpp"
#include "simulationParams.hpp"
#include "statistics.hpp"

namespace bs {

class Render {
  // Per ora lo lascio così perchè è più facile operarci sopra ma nel futuro
  // forse sarebbe meglio semplicemente farlo con due sf::RenderWindow, così ho
  // l'oggetto (classe) Render composta da due sf::Window
 private:
  sf::RenderWindow flockWindow_{sf::VideoMode(800, 600), "Flock Window",
                                sf::Style::Default};
  unsigned int flockWindowPositionX_{750};
  unsigned int flockWindowPositionY_{200};
  unsigned int flockWindowFps_{60};

  sf::RenderWindow statisticsWindow_{sf::VideoMode(600, 400), "Render Window",
                                     sf::Style::Default};
  unsigned int statisticsWindowPositionX_{0};
  unsigned int statisticsWindowPositionY_{200};
  unsigned int statisticsWindowFps_{60};

  // Dai un occhio al problema dell'inizializzazione di default per questo e
  // stats_
  sf::ConvexShape non_pred_boid_shape_{};
  sf::ConvexShape pred_boid_shape_{};
  sf::CircleShape detection_circle_{};
  sf::CircleShape danger_circle_{};
  sf::CircleShape cm_circle_{};

  Statistics stats_{};
  void calculateStats(std::vector<Boid> flock);

 public:
  Render();
  Render(SimParams const& sp);
  Render(std::vector<Boid> flock);

  bool isFWOpen() const;
  bool isSWOpen() const;
  V2D flockWindowDimensions() const;
  V2D statisticsWindowDimensions() const;
  sf::Text textOutput() const;

  void manageEvents();
  void manageWindowEvents(sf::RenderWindow& window);

  void renderFrame(std::vector<Boid> const& boids, SimParams const& parameters);
};

sf::ConvexShape makeBoidShape(sf::Color const& boidcolor);
sf::CircleShape makeCircleShape(double radius, sf::Color outline);
sf::CircleShape makeCenterDot();

}  // namespace bs

#endif