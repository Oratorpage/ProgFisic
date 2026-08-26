#include "render.hpp"

// In render devo racchiudere tutto e solamente quello che è necessario a
// sviluppare l'effettiva immagine che desidero

#include <cmath>
#include <string>

#include "simulation.hpp"

namespace bs {
constexpr double PI{3.14159265358979323846264338327950288};

Render::Render() = default;
// Immagino per i parametri di sfml di poterli inizializzare fino a quanto ho
// bisogno ed il resto saranno usati i parametri di default definiti dalle
// classi di sfml, mi sembra la forma più corretta
Render::Render(RenParams const& rp, BoidProperties const& bp)
    : ren_params_{rp},
      flockWindow_{sf::VideoMode(rp.flock_window_parameters.width,
                                 rp.flock_window_parameters.height),
                   rp.flock_window_parameters.title, sf::Style::Default},

      statisticsWindow_{sf::VideoMode(rp.statistics_window_parameters.width,
                                      rp.statistics_window_parameters.height),
                        rp.statistics_window_parameters.title,
                        sf::Style::Default},

      non_pred_boid_shape_{makeBoidShape(sf::Color::Cyan)},
      pred_boid_shape_{makeBoidShape(sf::Color::Red)},
      detection_circle_shape_{
          makeCircleShape(bp.detection_radius, sf::Color::Green)},
      danger_circle_shape_{makeCircleShape(bp.danger_radius, sf::Color::Red)},
      cm_circle_shape_{makeCenterDot()}

{
  flockWindow_.setFramerateLimit(rp.flock_window_parameters.fps);

  statisticsWindow_.setFramerateLimit(rp.statistics_window_parameters.fps);

  view_.setCenter({static_cast<float>(rp.flock_window_parameters.width / 2.),
                   static_cast<float>(rp.flock_window_parameters.height / 2.)});
  view_.setSize({static_cast<float>(rp.flock_window_parameters.width),
                 static_cast<float>(rp.flock_window_parameters.height)});
  initializeText(rp.font_path);
  renInvariant();
};  // 32 righe di costruttore, damn, fa un po' cagare così

void Render::renInvariant() {
  if (flockWindow_.getSize().x <= 0 || flockWindow_.getSize().y <= 0) {
    throw std::invalid_argument(
        "flockWindow dimensions are not acceptable, width and height cannot be "
        "less or equal to zero");
  }
  if (statisticsWindow_.getSize().x <= 0 ||
      statisticsWindow_.getSize().y <= 0) {
    throw std::invalid_argument(
        "statisticsWindow dimensions are not acceptable, width and height "
        "cannot be "
        "less or equal to zero");
  }
  // Come faccio un check su view_ statistics_text_ e le forme? basta verificare
  // che siano inizializzati?
}

bool Render::isFWOpen() const { return flockWindow_.isOpen(); }
bool Render::isSWOpen() const { return statisticsWindow_.isOpen(); }

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

void Render::initializeText(std::string const& path) {
  if (!(used_font_.loadFromFile(path))) {
    throw std::invalid_argument(
        "font not loaded correctly, try checking the font path");
  }
  statistics_text_.setFont(used_font_);
  statistics_text_.setCharacterSize(15);
  statistics_text_.setString("Invalid");
}
// I created this function and decided not to put the position setting directly
// in the constructor because I was having issues positioning the second window
void Render::setWindowsPosition(RenParams const& rp) {
  flockWindow_.setPosition(
      {rp.flock_window_parameters.posX, rp.flock_window_parameters.posY});
  statisticsWindow_.setPosition({rp.statistics_window_parameters.posX,
                                 rp.statistics_window_parameters.posY});
};

void Render::renderFrame(Simulation const& sim) {
  flockWindow_.clear(sf::Color(150, 150, 150));
  statisticsWindow_.clear(sf::Color(150, 150, 150));
  // flockWindow_.setPosition({750,200});

  for (auto const& b : sim.currentFlock()) {
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
    // deve fare solamente una cosa per volta, lo sposto in una funzione
    // visibleRad()
    if (ren_params_.op_rad) {
      detection_circle_shape_.setPosition(static_cast<float>(p.x),
                                          static_cast<float>(p.y));
      danger_circle_shape_.setPosition(static_cast<float>(p.x),
                                       static_cast<float>(p.y));
      flockWindow_.draw(detection_circle_shape_);
      flockWindow_.draw(danger_circle_shape_);
    }

    if (b.IsPredator()) {
      flockWindow_.draw(pred_boid_shape_);
    } else {
      flockWindow_.draw(non_pred_boid_shape_);
    }
  }

  cm_circle_shape_.setPosition(
      static_cast<float>(sim.currentStatistics().cm_pos.x),
      static_cast<float>(sim.currentStatistics().cm_pos.y));

  flockWindow_.draw(cm_circle_shape_);

  statistics_text_.setString(sim.currentStatistics().statistics_output);

  statisticsWindow_.draw(statistics_text_);
  statisticsWindow_.display();
  flockWindow_.display();
}

// Caratteristiche grafiche del boid

// Per questi secondo me se vale per simulation, può essere adottata la stessa
// regola: se non c'è altro modo di utilizzarli in maniera impropria allora
// automaticamente o si inizializzano manualmente o l'unica funzione chiamabile
// sulla classe sarà direttamente responsabile per l'inizializzazione
sf::ConvexShape makeBoidShape(sf::Color const& boidcolor) {
  sf::ConvexShape boid;
  boid.setPointCount(3);
  boid.setPoint(0, {20.f, 0.f});    // nose
  boid.setPoint(1, {-10.f, -8.f});  // back-down/right
  boid.setPoint(2, {-10.f, 8.f});   // back-up/left
  // This shape does not need to be given a new origin as the up-left corner
  // from which it originates is already the center of the boid
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