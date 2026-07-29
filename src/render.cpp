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

Render::Render(std::vector<Boid> flock) { calculateStats(flock); }

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

void Render::calculateStats(std::vector<Boid> flock) {
  stats_.cm_pos = {0, 0};
  stats_.avg_vel = {0, 0};
  stats_.in_window_count = {0};
  for (Boid b : flock) {
    V2D p = b.Pos();
    V2D v = b.Vel();

    if (b.Pos().x < static_cast<double>(flockWindow_.getSize().x) &&
        b.Pos().y < static_cast<double>(flockWindow_.getSize().y) &&
        b.Pos().x > 0 && b.Pos().y > 0) {
      ++stats_.in_window_count;
    }
    stats_.cm_pos += p;
    stats_.avg_vel += v;
  }
  stats_.cm_pos = stats_.cm_pos / static_cast<double>(flock.size());
  stats_.avg_vel = stats_.avg_vel / static_cast<double>(flock.size());

  std::string cm_string{
      "Position of the cm_pos: x :" + std::to_string(stats_.cm_pos.x) +
      " , y: " + std::to_string(stats_.cm_pos.y) + "\n"};
  std::string avg_vel_string{"Average velocity of the total flock: x :" +
                             std::to_string(stats_.avg_vel.x) + " , y: " +
                             std::to_string(stats_.avg_vel.y) + "\n"};
  std::string in_view_string{"Boids present in window view: " +
                             std::to_string(stats_.in_window_count) + "\n"};

  std::string fps_string{
      "flockwindow fps: " + std::to_string(flockWindowFps_) + "\n" +
      "statisticswindow fps:" + std::to_string(statisticsWindowFps_) + "\n"};

  stats_.output.setString(cm_string + avg_vel_string + in_view_string +
                          fps_string);
}

void Render::renderFrame(std::vector<Boid> const& flock,
                         SimParams const& parameters,
                         sf::ConvexShape& non_pred_boid,
                         sf::ConvexShape& pred_boid,
                         sf::CircleShape& detection_circle,
                         sf::CircleShape& danger_circle,
                         sf::CircleShape& cm_circle) {
  flockWindow_.clear(sf::Color(150, 150, 150));
  statisticsWindow_.clear(sf::Color(150, 150, 150));
  // Questi oggetti si potrebbero mettere in una struct (o classe) statistics
  // per tenerlo ordinato e fare fare una cosa per volta alla funzione ma non so
  // se possa funzionare, sarebbe scomodo passare gli argomenti attraverso due
  // funzioni se posso restituire un solo argomento per funzione

  // Prima di eliminare questa cosa qua, mi rendo conto dopo aver fatto la
  // funzione per la statistica che si potevano tenere questi dati ed usarli per
  // disegnare una freccia che indica la velocità media dello stormo (posta nel
  // centro della finestra) e come prima il cm; questo è opzionale ma sarebbe
  // carino, e prima di eliminarlo da qua devo decidere come strutturarlo
  V2D cm_pos;

  for (auto const& b : flock) {
    V2D p = b.Pos();
    V2D v = b.Vel();
    // Questo ha un problema di angoli limiti che va risolto, v.x ==0; guardando
    // la documentazinoe direi basti fare un if case ed in base al segno di v.y
    // allora bisogna invertire il segno che ritorna  atan2 perchè sfml è al
    // contrario
    double ang = std::atan2(v.y, v.x) * 180.0 / PI;
    if (b.IsPredator()) {
      pred_boid.setRotation(static_cast<float>(ang));
      pred_boid.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
    } else {
      non_pred_boid.setRotation(static_cast<float>(ang));
      non_pred_boid.setPosition(static_cast<float>(p.x),
                                static_cast<float>(p.y));
    }
    // Possible bug/weird behaviour for non toroidal space but oprad on, kinda,
    // takes longer time to update so it iteracts less, need to fix
    if (parameters.op_rad) {
      detection_circle.setPosition(static_cast<float>(p.x),
                                   static_cast<float>(p.y));
      danger_circle.setPosition(static_cast<float>(p.x),
                                static_cast<float>(p.y));
      flockWindow_.draw(detection_circle);
      flockWindow_.draw(danger_circle);
    }

    if (b.IsPredator()) {
      flockWindow_.draw(pred_boid);
    } else {
      flockWindow_.draw(non_pred_boid);
    }

    cm_pos += p;
  }
  cm_pos = cm_pos / static_cast<double>(flock.size());
  cm_circle.setPosition(static_cast<float>(cm_pos.x),
                        static_cast<float>(cm_pos.y));

  flockWindow_.draw(cm_circle);

  statisticsWindow_.draw(textOutput());

  statisticsWindow_.display();
  flockWindow_.display();
}

// OK tolgo le statistics da renderFrame perchè tanto se io gli passo lo struct
// statistics dopo posso prendere da lì e usarlo per fare freccia o quello che
// desidero

// La cosa che mi rompe di questo è che invece di avere un oggetto che esiste ed
// è costante nella memoria e semplicemente altre funzioni lo leggono e lo usano
// per altro, verrebbe creato da nuovo ogni volta, questa è la cosa che più mi
// scoccia e che voglio evitare nel codice, un'espansione e contrazione dello
// stack, piuttosto che sia più grande ma vari di poco

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