// Manages the render of the windows and the shapes
#ifndef FLOCK_RENDER_HPP
#define FLOCK_RENDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Boid.hpp"
#include "SimParams.hpp"

namespace flock {
sf::ConvexShape MakeBoidShape(sf::Color const& boidcolor);
sf::CircleShape MakeCircleShape(double radius, sf::Color outline);
sf::CircleShape MakeCenterDot();

void RenderFrame(sf::RenderWindow& flockwindow, sf::RenderWindow& iowindow,
                 std::vector<Boid> const& boids, SimParams const& params,
                 V2D const& fwstsize, sf::ConvexShape& non_pred_boid,
                 sf::ConvexShape& pred_boid, sf::CircleShape& detectcirc,
                 sf::CircleShape& dangercirc, sf::CircleShape& cmpos,
                 sf::Text& statistics);
}  // namespace flock

#endif