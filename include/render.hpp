// Manages the render of the windows and the shapes
#ifndef FLOCK_RENDER_HPP
#define FLOCK_RENDER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "boid.hpp"
#include "simParams.hpp"

namespace flock {
sf::ConvexShape makeBoidShape(sf::Color const& boidcolor);
sf::CircleShape makeCircleShape(double radius, sf::Color outline);
sf::CircleShape makeCenterDot();

void renderFrame(sf::RenderWindow& FlockWindow, sf::RenderWindow& IoWindow,
                 std::vector<Boid> const& boids, SimParams const& parameters,
                 V2D const& flock_window_size_d, sf::ConvexShape& non_pred_boid,
                 sf::ConvexShape& pred_boid, sf::CircleShape& detection_circle,
                 sf::CircleShape& danger_circle, sf::CircleShape& cm_circle,
                 sf::Text& statistics);
}  // namespace flock

#endif