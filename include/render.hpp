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

  sf::ConvexShape non_pred_boid_shape_;
  sf::ConvexShape pred_boid_shape_;
  sf::CircleShape detection_circle_shape_;
  sf::CircleShape danger_circle_shape_;
  sf::CircleShape cm_circle_shape_;

  sf::View view_;
  sf::Text statistics_text_;

  // qua posso fare una funzione ausiliaria che mi restituisca un int di quanti
  // boid sono visibili a schermo, poi grazie alla struttura di conductor così,
  // posso chiamarla prima renderFrame e da lì passo l'int a sim_.stats_ e poi
  // faccio renderFrame, così le statistiche calcolate da sim_tick() si
  // combinano con quell'int e sono complete e poi quando faccio renderFrame ho
  // tutto, e per ogni ciclo è così, la combinazione avviene poco prima del
  // render e dopo è corretto; correzione, dopo dovrei modificare
  // statistics_output non solo in_window_count perchè render prende la stringa
  // che poi la fa diventare un oggetto sfml::Text

  void renInvariant();

 public:
  Render();
  Render(RenParams const& sp, BoidProperties const& bp);

  bool isFWOpen() const;
  bool isSWOpen() const;

  void manageEvents();
  void manageWindowEvents(sf::RenderWindow& window);

  void initializeText(std::string const& path);

  void renderFrame(Simulation const& simulation);
};

// queste qua o le definisco inline o le metto come metodi
sf::ConvexShape makeBoidShape(sf::Color const& boidcolor);
sf::CircleShape makeCircleShape(double radius, sf::Color outline);
sf::CircleShape makeCenterDot();

}  // namespace bs

#endif