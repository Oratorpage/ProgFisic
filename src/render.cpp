#include "render.hpp"

#include <cmath>
#include <string>

namespace flock {
constexpr double PI{3.14159265358979323846264338327950288};

// Caratteristiche grafiche del boid
sf::ConvexShape makeBoidShape(sf::Color const& boidcolor) {
  sf::ConvexShape boid;
  boid.setPointCount(3);
  boid.setPoint(0, {20.f, 0.f});    // nose
  boid.setPoint(1, {-10.f, -8.f});  // back-down/right
  boid.setPoint(2, {-10.f, 8.f});   // back-up/left
  // This shape does not need an origin as the up-left corner from which it
  // originates is already in the perfect spot to represent the boid
  boid.setFillColor(boidcolor);
  boid.setOutlineThickness(0.5f);
  boid.setOutlineColor(sf::Color::Black);
  boid.setPosition(0, 0);
  return boid;
}

sf::CircleShape makeCircleShape(double radius, sf::Color outline) {
  sf::CircleShape circ;
  circ.setRadius(static_cast<float>(radius));
  circ.setOrigin(static_cast<float>(radius), static_cast<float>(radius));
  circ.setOutlineColor(outline);
  circ.setFillColor(sf::Color::Transparent);
  circ.setOutlineThickness(5.f);
  return circ;
}

sf::CircleShape makeCenterDot() {
  sf::CircleShape cm_pos;
  cm_pos.setRadius(5.f);
  cm_pos.setOrigin(5.f, 5.f);
  cm_pos.setOutlineColor(sf::Color::Black);
  cm_pos.setFillColor(sf::Color::Black);
  return cm_pos;
}

void renderFrame(sf::RenderWindow& FlockWindow, sf::RenderWindow& IoWindow,
                 std::vector<Boid> const& boids, SimParams const& parameters,
                 V2D const& flock_window_size_d, sf::ConvexShape& non_pred_boid,
                 sf::ConvexShape& pred_boid, sf::CircleShape& detection_circle,
                 sf::CircleShape& danger_circle, sf::CircleShape& cm_circle,
                 sf::Text& statistics) {
  FlockWindow.clear(sf::Color(150, 150, 150));

  V2D cm_pos;
  V2D avg_vel;
  int in_window_count{0};

  for (auto const& b : boids) {
    V2D p = b.Pos();
    V2D v = b.Vel();
    // Questo ha un problema di angoli limiti che va risolto, v.x ==0
    double ang = std::atan2(v.y, v.x) * 180.0 / PI;
    if (b.IsPred()) {
      pred_boid.setRotation(static_cast<float>(ang));
      pred_boid.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
    } else {
      non_pred_boid.setRotation(static_cast<float>(ang));
      non_pred_boid.setPosition(static_cast<float>(p.x),
                                static_cast<float>(p.y));
    }
    // Possible bug/weird behaviour for non toroidal space but oprad on
    if (parameters.op_rad) {
      detection_circle.setPosition(static_cast<float>(p.x),
                                   static_cast<float>(p.y));
      danger_circle.setPosition(static_cast<float>(p.x),
                                static_cast<float>(p.y));
      FlockWindow.draw(detection_circle);
      FlockWindow.draw(danger_circle);
    }

    if (b.Pos().x < flock_window_size_d.x &&
        b.Pos().y < flock_window_size_d.y && b.Pos().x > 0 && b.Pos().y > 0) {
      ++in_window_count;
    }
    if (b.IsPred()) {
      FlockWindow.draw(pred_boid);
    } else {
      FlockWindow.draw(non_pred_boid);
    }

    cm_pos += p;
    avg_vel += v;
  }
  cm_pos = cm_pos / static_cast<double>(boids.size());
  avg_vel = avg_vel / static_cast<double>(boids.size());

  std::string cm_string{
      "Position of the cm_pos: x :" + std::to_string(cm_pos.x) +
      " , y: " + std::to_string(cm_pos.y) + "\n"};
  std::string avg_vel_string{
      "Velocity of the total flock: x :" + std::to_string(avg_vel.x) +
      " , y: " + std::to_string(avg_vel.y) + "\n"};
  std::string strinwc{"Boids present in window view: " +
                      std::to_string(in_window_count) + "\n"};

  statistics.setString(cm_string + avg_vel_string + strinwc);

  cm_circle.setPosition(static_cast<float>(cm_pos.x),
                        static_cast<float>(cm_pos.y));
  FlockWindow.draw(cm_circle);

  IoWindow.clear(sf::Color(150, 150, 150));
  IoWindow.draw(statistics);

  IoWindow.display();
  FlockWindow.display();
}

}  // namespace flock