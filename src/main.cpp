#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "boid.hpp"
#include "input.hpp"
#include "rand.hpp"
#include "render.hpp"
#include "vChange.hpp"

// Forse va tutto messo dopo flock_window_size_d nel ciclo while della finestra

int main() {
  try {
    // Questa parte qua, da qua
    sf::RenderWindow FlockWindow(sf::VideoMode(800, 600), "Flock View",
                                 sf::Style::Default);
    FlockWindow.setPosition(sf::Vector2i(750, 200));

    sf::RenderWindow IoWindow(sf::VideoMode(600, 400), "I/O View",
                              sf::Style::Default);
    IoWindow.setPosition(sf::Vector2i(0, 200));

    flock::V2D flock_window_size_d{
        static_cast<double>(FlockWindow.getSize().x),
        static_cast<double>(FlockWindow.getSize().y)};

    std::string const path{"parameters.txt"};
    flock::SimParams parameters{flock::readFileParams(path)};
    // Fino a qua, lo voglio rendere modificabile attraverso file di
    // configurazione, non tramite cambio di codice, dunque devo implementare
    // una struttura per renderlo possibile
    std::vector<flock::Boid> boids;
    int tot_boids{parameters.pred_boidnum + parameters.non_pred_boidnum};

    boids.reserve(static_cast<long unsigned int>(tot_boids));

    for (int i{0}; i < parameters.non_pred_boidnum; ++i) {
      boids.emplace_back(flock::randVel(), flock::randPos(flock_window_size_d));
    }
    for (int i{0}; i < parameters.pred_boidnum; ++i) {
      boids.emplace_back(flock::randVel(), flock::randPos(flock_window_size_d),
                         true);
    }

    sf::ConvexShape non_pred_boid{flock::makeBoidShape(sf::Color::Cyan)};
    sf::ConvexShape pred_boid{flock::makeBoidShape(sf::Color::Red)};
    sf::CircleShape detection_circle{
        flock::makeCircleShape(parameters.detection_rad, sf::Color::Green)};
    sf::CircleShape danger_circle{
        flock::makeCircleShape(parameters.danger_rad, sf::Color::Red)};
    sf::CircleShape cm_circle{flock::makeCenterDot()};

    sf::Font out_font;
    // Questo deve essere letto dalla directory corrente o da un include dunque
    // non va bene per ora
    if (out_font.loadFromFile(
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
      std::cout << "Font file was  loaded correctly \n";
    }

    sf::Text statistics;
    statistics.setFont(out_font);
    statistics.setCharacterSize(15);

    sf::Clock clock;

    // Questo anche lo dovrei aggiungere nel render, relegarlo a quello
    while (FlockWindow.isOpen()) {
      sf::Event event;
      while (FlockWindow.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            FlockWindow.close();
            break;

          case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
              FlockWindow.close();
            }
            break;
          default:
            break;
        }
      }
      // chiamare close su finestra già chiusa
      while (IoWindow.isOpen() && IoWindow.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            IoWindow.close();
            break;

          case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
              IoWindow.close();
            }
            break;
          default:
            break;
        }
      }
      // Sistema il clock in modo che il dt sia costante 0.00833 0.01667
      // Questo adesso provo a normalizzarlo a costante tramite un elapsed come
      // game loop documentazione sfml poi se funzia bene e lo lascio così, se
      // no dt fluttuante
      double dt{clock.restart().asSeconds()};
      // Avere il dt costante sistemerebbe anche il problema di interazione
      // quando c'è tanto da calcolare, come nel caso di oprad true
      flock::velocityChangeBoids(boids, dt, flock_window_size_d, parameters);

      flock::renderFrame(FlockWindow, IoWindow, boids, parameters,
                         flock_window_size_d, non_pred_boid, pred_boid,
                         detection_circle, danger_circle, cm_circle, statistics,
                         dt);
    }
  } catch (std::exception const& err) {
    std::cerr << err.what() << "\n";
    return 1;
  }
}
// Controlla se è il distruttore che elimina IoWindow oppure se è la logica
// del programma