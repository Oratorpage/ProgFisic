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
Render::Render(RenParams const& rp)
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
      // Per esempio infatti cm_circle non mi serve e non lo posso usare se non
      // separatamente prima, l'unica funzione che lo può cambiare è
      // renderFrame()
      statistics_text_{}  // Ha senso fare così?

{
  flockWindow_.setFramerateLimit(rp.flock_window_parameters.fps);
  flockWindow_.setPosition(
      {rp.flock_window_parameters.posX, rp.flock_window_parameters.posY});

  statisticsWindow_.setFramerateLimit(rp.statistics_window_parameters.fps);
  statisticsWindow_.setPosition({rp.statistics_window_parameters.posX,
                                 rp.statistics_window_parameters.posY});

  view_.setCenter({static_cast<float>(rp.flock_window_parameters.width / 2.),
                   static_cast<float>(rp.flock_window_parameters.height / 2.)});
  view_.setSize({static_cast<float>(rp.flock_window_parameters.width),
                 static_cast<float>(rp.flock_window_parameters.height)});
  // Dovrei inizializzare pure il testo? Che noia
};  // 22 righe di costruttore, damn, fa un po' cagare così

bool Render::isFWOpen() const { return flockWindow_.isOpen(); }
bool Render::isSWOpen() const { return statisticsWindow_.isOpen(); }
V2D const& Render::flockWindowDimensions() const {
  return {static_cast<double>(flockWindow_.getSize().x),
          static_cast<double>(flockWindow_.getSize().y)};
}
V2D const& Render::statisticsWindowDimensions() const {
  return {static_cast<double>(statisticsWindow_.getSize().x),
          static_cast<double>(statisticsWindow_.getSize().y)};
}

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

void Render::renderFrame(Simulation const& sim) {
  flockWindow_.clear(sf::Color(150, 150, 150));
  statisticsWindow_.clear(sf::Color(150, 150, 150));

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
  }

  cm_circle_.setPosition(static_cast<float>(sim.currentStatistics().cm_pos.x),
                         static_cast<float>(sim.currentStatistics().cm_pos.y));

  flockWindow_.draw(cm_circle_);

  // È meglio fare così ed avere l'immediata variazione (anche se non si vede
  // dal conductor che questa cosa sta venendo fatta? ) piuttosto che chiamare
  // il calcolo del calcolo delle statistiche direttamente dal conduttore?
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