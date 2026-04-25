#include "Render.hpp"

#include <cmath>
#include <string>

namespace flock {
constexpr double PI{3.14159265358979323846264338327950288};

// Caratteristiche grafiche del boid
sf::ConvexShape MakeBoidShape() {
  sf::ConvexShape tri;
  tri.setPointCount(3);
  tri.setPoint(0, {20.f, 0.f});    // nose
  tri.setPoint(1, {-10.f, -8.f});  // back-left
  tri.setPoint(2, {-10.f, 8.f});   // back-right
  tri.setFillColor(sf::Color::Cyan);
  tri.setOutlineThickness(0.5f);
  tri.setOutlineColor(sf::Color::Black);
  tri.setPosition(0, 0);
  return tri;
}

sf::CircleShape MakeCircleShape(double radius, sf::Color outline) {
  sf::CircleShape circ;
  circ.setRadius(static_cast<float>(radius));
  circ.setOrigin(static_cast<float>(radius), static_cast<float>(radius));
  circ.setOutlineColor(outline);
  circ.setFillColor(sf::Color::Transparent);
  circ.setOutlineThickness(5.f);
  return circ;
}

sf::CircleShape MakeCenterDot() {
  sf::CircleShape cm;
  cm.setRadius(5.f);
  cm.setOutlineColor(sf::Color::Black);
  cm.setFillColor(sf::Color::Black);
  return cm;
}

void RenderFrame(sf::RenderWindow& flockwindow, sf::RenderWindow& iowindow,
                 std::vector<Boid> const& boids, SimParams const& params,
                 V2D const& fwstsize, sf::ConvexShape& tri,
                 sf::CircleShape& detectcirc, sf::CircleShape& dangercirc,
                 sf::CircleShape& cmpos, sf::Text& statistics) {
  flockwindow.clear(sf::Color(150, 150, 150));

  V2D cm;
  V2D avgvel;
  int inwcount{0};

  for (auto const& b : boids) {
    V2D p = b.Pos();
    V2D v = b.Vel();
    double ang = std::atan2(v.y, v.x) * 180.0 / PI;
    tri.setRotation(static_cast<float>(ang));
    tri.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
    // Possible bug/weird behaviour for non toroidal space but oprad on
    if (params.oprad) {
      detectcirc.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
      dangercirc.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
      flockwindow.draw(detectcirc);
      flockwindow.draw(dangercirc);
    }

    if (b.Pos().x < fwstsize.x && b.Pos().y < fwstsize.y && b.Pos().x > 0 &&
        b.Pos().y > 0) {
      ++inwcount;
    }
    flockwindow.draw(tri);

    cm += p;
    avgvel += v;
  }
  cm = cm / static_cast<double>(boids.size());
  avgvel = avgvel / static_cast<double>(boids.size());

  std::string cmstring = "Position of the cm: x :" + std::to_string(cm.x) +
                         " , y: " + std::to_string(cm.y) + "\n";
  std::string avgvelstring =
      "Velocity of the total flock: x :" + std::to_string(avgvel.x) +
      " , y: " + std::to_string(avgvel.y) + "\n";
  std::string strinwc =
      "Boids present in window view: " + std::to_string(inwcount) + "\n";

  statistics.setString(cmstring + avgvelstring + strinwc);

  cmpos.setPosition(static_cast<float>(cm.x), static_cast<float>(cm.y));
  flockwindow.draw(cmpos);

  iowindow.clear(sf::Color(150, 150, 150));
  iowindow.draw(statistics);

  iowindow.display();
  flockwindow.display();
}

}  // namespace flock