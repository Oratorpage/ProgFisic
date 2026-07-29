#include "render.hpp"

#include <cmath>
#include <string>

namespace bs {
constexpr double PI{3.14159265358979323846264338327950288};

Render::Render() = default;
Render::Render(SimParams const& sp)
    : flockWindow_{sf::VideoMode(sp.flockWindowWidth, sp.flockWindowHeight),
                   sp.flockWindowTitle, sf::Style::Default},
      flockWindowPositionX_{sp.flockWindowPositionX},
      flockWindowPositionY_{sp.flockWindowPositionY},
      flockWindowFps_{sp.flockWindowFps},
      statisticsWindow_{
          sf::VideoMode(sp.statisticsWindowWidth, sp.statisticsWindowHeight),
          sp.statisticsWindowTitle, sf::Style::Default},
      statisticsWindowPositionX_{sp.statisticsWindowPositionX},
      statisticsWindowPositionY_{sp.flockWindowPositionY},
      statisticsWindowFps_{sp.statisticsWindowFps},
      non_pred_boid_shape_{makeBoidShape(sf::Color::Cyan)},
      pred_boid_shape_{makeBoidShape(sf::Color::Red)},
      detection_circle_{makeCircleShape(sp.detection_rad, sf::Color::Green)},
      danger_circle_{makeCircleShape(sp.danger_rad, sf::Color::Red)},
      cm_circle_{makeCenterDot()} {
  flockWindow_.setFramerateLimit(flockWindowFps_);
  flockWindow_.setPosition({flockWindowPositionX_, flockWindowPositionY_});

  statisticsWindow_.setFramerateLimit(statisticsWindowFps_);
  statisticsWindow_.setPosition(
      {statisticsWindowPositionX_, statisticsWindowPositionY_});
};  // 23 righe di costruttore, damn, fa un po' cagare così


bool Render::isFWOpen() const { return flockWindow_.isOpen(); }
bool Render::isSWOpen() const { return statisticsWindow_.isOpen(); }
V2D Render::flockWindowDimensions() const {
  return {static_cast<double>(flockWindow_.getSize().x),
          static_cast<double>(flockWindow_.getSize().y)};
}
V2D Render::statisticsWindowDimensions() const {
  return {static_cast<double>(statisticsWindow_.getSize().x),
          static_cast<double>(statisticsWindow_.getSize().y)};
}
sf::Text Render::textOutput() const { return stats_.output; }

void Render::manageEvents() {
  manageWindowEvents(flockWindow_);

  if (statisticsWindow_.isOpen()) {
    manageWindowEvents(statisticsWindow_);
  }

  if (!flockWindow_.isOpen() && statisticsWindow_.isOpen()) {
    statisticsWindow_.close();
  }
}

void Render::manageWindowEvents(sf::RenderWindow& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Q) {
          window.close();
          break;
        }

      default:
        break;
    }
  }
}

void Render::renderFrame(std::vector<Boid> const& flock,
                         SimParams const& parameters) {
  flockWindow_.clear(sf::Color(150, 150, 150));
  statisticsWindow_.clear(sf::Color(150, 150, 150));
  
  V2D cm_pos;

  for (auto const& b : flock) {
    V2D p = b.Pos();
    V2D v = b.Vel();
    // Questo ha un problema di angoli limiti che va risolto, v.x ==0; guardando
    // la documentazinoe direi basti fare un if case ed in base al segno di v.y
    // allora bisogna invertire il segno che ritorna  atan2 perchè sfml è al
    // contrario
    // Questo ulteriormente lo potrei spostare in una funzione separata,
    // rotate()
    double ang = std::atan2(v.y, v.x) * 180.0 / PI;
    if (b.IsPredator()) {
      pred_boid_shape_.setRotation(static_cast<float>(ang));
      pred_boid_shape_.setPosition(static_cast<float>(p.x),
                                   static_cast<float>(p.y));
    } else {
      non_pred_boid_shape_.setRotation(static_cast<float>(ang));
      non_pred_boid_shape_.setPosition(static_cast<float>(p.x),
                                       static_cast<float>(p.y));
    }
    // Questo lo voglio lasciare che fa il check ogni volta? Lo divido in due
    // funzioni in modo che non debba fare il check ogni volta? C'è un ulteriore
    // modo per farlo in maniera carina e abbassare il consumo di memoria/numero
    // operazioni? Inoltre sistemerei anche un po' il problema del ogni funzione
    // deve fare solamente una cosa per volta
    if (parameters.op_rad) {
      detection_circle_.setPosition(static_cast<float>(p.x),
                                    static_cast<float>(p.y));
      danger_circle_.setPosition(static_cast<float>(p.x),
                                 static_cast<float>(p.y));
      flockWindow_.draw(detection_circle_);
      flockWindow_.draw(danger_circle_);
    }

    if (b.IsPredator()) {
      flockWindow_.draw(pred_boid_shape_);
    } else {
      flockWindow_.draw(non_pred_boid_shape_);
    }

    cm_pos += p;
  }
  cm_pos = cm_pos / static_cast<double>(flock.size());
  cm_circle_.setPosition(static_cast<float>(cm_pos.x),
                         static_cast<float>(cm_pos.y));

  flockWindow_.draw(cm_circle_);

  statisticsWindow_.draw(textOutput());

  statisticsWindow_.display();
  flockWindow_.display();
}

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
  sf::CircleShape center_pos;
  center_pos.setRadius(5.f);
  center_pos.setOrigin(5.f, 5.f);
  center_pos.setOutlineColor(sf::Color::Black);
  center_pos.setFillColor(sf::Color::Black);
  return center_pos;
}

}  // namespace bs