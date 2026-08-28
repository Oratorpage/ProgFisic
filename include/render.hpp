// Manages the render of the windows and the shapes
#ifndef BS_RENDER_HPP
#define BS_RENDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "boid.hpp"
#include "renderParams.hpp"
#include "simulation.hpp"

namespace bs {
// Specialized class to manage a render with the external library sfml
class Render {
 private:
  RenParams ren_params_;
  sf::RenderWindow flockWindow_{sf::VideoMode(800, 600), "Temp Window 1",
                                sf::Style::Default};

  sf::RenderWindow statisticsWindow_{sf::VideoMode(600, 400), "Temp Window 2",
                                     sf::Style::Default};

  sf::ConvexShape non_pred_boid_shape_;
  sf::ConvexShape pred_boid_shape_;
  sf::CircleShape detection_circle_shape_;
  sf::CircleShape danger_circle_shape_;
  sf::CircleShape cm_circle_shape_;

  sf::Font used_font_;
  sf::View view_;
  sf::Text statistics_text_;

  void renInvariant();

 public:
  Render(RenParams const& rp, BoidProperties const& bp);

  bool isFWOpen() const;
  bool isSWOpen() const;

  void manageEvents();
  void manageWindowEvents(sf::RenderWindow& window);

  void initializeText(std::string const& path);
  void setWindowsPosition(RenParams const& rp);

  void renderFrame(Simulation const& simulation);
};

// queste qua o le definisco inline o le metto come metodi
sf::ConvexShape makeBoidShape(sf::Color const& boidcolor);
sf::CircleShape makeCircleShape(double radius, sf::Color outline);
sf::CircleShape makeCenterDot();

}  // namespace bs

#endif