#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Boid.hpp"
#include "Input.hpp"
#include "Rand.hpp"
#include "Render.hpp"
#include "VChange.hpp"

// g++ -std=c++17 boids.cpp -lsfml-graphics -lsfml-window -lsfml-system

// Should maybe implement the try catch architecture
int main() {
  try {
    sf::RenderWindow flockwindow(sf::VideoMode(800, 600), "Flock View",
                                 sf::Style::Default);
    flockwindow.setPosition(sf::Vector2i(750, 200));

    sf::RenderWindow iowindow(sf::VideoMode(600, 400), "I/O View",
                              sf::Style::Default);

    flock::V2D fwstsize{static_cast<double>(flockwindow.getSize().x),
                        static_cast<double>(flockwindow.getSize().y)};

    flock::SimParams parameters{flock::readparams()};
    std::vector<flock::Boid> boids;
    long unsigned int tot_boids{parameters.pred_boidnum + parameters.non_pred_boidnum};
    boids.reserve(tot_boids);

    for (long unsigned int i{0}; i < parameters.non_pred_boidnum; ++i) {
      boids.emplace_back(flock::randvel(), flock::randpos(fwstsize));
    }
    for (long unsigned int i{0}; i < parameters.pred_boidnum; ++i) {
      boids.emplace_back(flock::randvel(), flock::randpos(fwstsize), true);
    }


    sf::ConvexShape non_pred_boid{flock::MakeBoidShape(sf::Color::Cyan)};
    sf::ConvexShape pred_boid{flock::MakeBoidShape(sf::Color::Red)};
    sf::CircleShape detectcirc{
        flock::MakeCircleShape(parameters.detectrad, sf::Color::Green)};
    sf::CircleShape dangercirc{
        flock::MakeCircleShape(parameters.dangerrad, sf::Color::Red)};
    sf::CircleShape cm{flock::MakeCenterDot()};

    sf::Font tnrfont;
    if (tnrfont.loadFromFile(
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
      std::cout << "Font file was  loaded correctly \n";
    }

    sf::Text statistics;
    statistics.setFont(tnrfont);
    statistics.setCharacterSize(15);

    sf::Clock clock;

    while (flockwindow.isOpen()) {
      sf::Event event;
      while (flockwindow.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            flockwindow.close();
            break;

          case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
              flockwindow.close();
            }
            break;
          default:
            break;
        }
      }
      // chiamare close su finestra già chiusa
      while (iowindow.isOpen() && iowindow.pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            iowindow.close();
            break;

          case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
              iowindow.close();
            }
            break;
          default:
            break;
        }
      }
      // Sistema il clock in modo che il dt sia costante
      double dt = clock.restart().asSeconds();

      flock::VChangeBoids(boids, dt, fwstsize, parameters);

      flock::RenderFrame(flockwindow, iowindow, boids, parameters, fwstsize,
                         non_pred_boid, pred_boid, detectcirc, dangercirc, cm, statistics);
    }
  } catch (std::exception const& err) {
    std::cerr << err.what() << "\n";
    return 1;
  }
}
// Controlla se è il distruttore che elimina iowindow oppure se è la logica
// del programma