// Manages the render of the windows and the shapes
#ifndef BS_RENDER_HPP
#define BS_RENDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "boid.hpp"
#include "renderParams.hpp"

namespace bs {

class Render {
 private:
  RenParams ren_params_;
  sf::RenderWindow flockWindow_{sf::VideoMode(800, 600), "Flock Window",
                                sf::Style::Default};

  sf::RenderWindow statisticsWindow_{sf::VideoMode(600, 400), "Render Window",
                                     sf::Style::Default};

  // Dai un occhio al problema dell'inizializzazione di default per questo.
  // Immagino che sia di assicurarsi che non possa essere usato a meno che non
  // sia stato inizializzato per evitare undefined behaviour
  sf::ConvexShape non_pred_boid_shape_;
  sf::ConvexShape pred_boid_shape_;
  sf::CircleShape detection_circle_;
  sf::CircleShape danger_circle_;
  sf::CircleShape cm_circle_;

  sf::View view_;
  sf::Text statistics_text_;
  

 public:
  Render();
  Render(RenParams const& sp);

  bool isFWOpen() const;
  bool isSWOpen() const;
  V2D const& flockWindowDimensions() const;
  V2D const& statisticsWindowDimensions() const;

  void manageEvents();
  void manageWindowEvents(sf::RenderWindow& window);

  void renderFrame(Simulation const& simulation);
};

sf::ConvexShape makeBoidShape(sf::Color const& boidcolor);
sf::CircleShape makeCircleShape(double radius, sf::Color outline);
sf::CircleShape makeCenterDot();

}  // namespace bs

#endif