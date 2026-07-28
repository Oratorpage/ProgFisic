#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "boid.hpp"
#include "conductor.hpp"
#include "input.hpp"
#include "rand.hpp"

int main() {
  try {
    /*












    Ok facciamo pulizia











     Qua ci deve andare la parte inerente al parsing del nome del file di
     configurazione, argv e argc










    */

    double time_factor{};
    bs::SimParams parameters{};
    bs::Conductor application{parameters, time_factor};

    application.start(parameters);

    ////////////////////////////////////////////////////////////
    // Questa parte qua, da qua
    sf::RenderWindow FlockWindow(sf::VideoMode(800, 600), "Flock View",
                                 sf::Style::Default);
    FlockWindow.setPosition(sf::Vector2i(750, 200));

    sf::RenderWindow IoWindow(sf::VideoMode(600, 400), "I/O View",
                              sf::Style::Default);
    IoWindow.setPosition(sf::Vector2i(0, 200));

    bs::V2D flock_window_size_d{static_cast<double>(FlockWindow.getSize().x),
                                static_cast<double>(FlockWindow.getSize().y)};
    // Fino a qua, lo voglio rendere modificabile attraverso file di
    // configurazione, non tramite cambio di codice, dunque devo implementare
    // una struttura per renderlo possibile

    // Questo va sistemato tramite argv e argc
    std::string const path{"standard_parameters.txt"};
    bs::SimParams parameters{bs::readSimulationParams(path)};

    std::vector<bs::Boid> boids;
    int tot_boids{};

    boids.reserve(static_cast<long unsigned int>(tot_boids));

    for (int i{0}; i < parameters.non_pred_boidnum; ++i) {
      boids.emplace_back(bs::randVel(), bs::randPos(flock_window_size_d));
    }
    for (int i{0}; i < parameters.pred_boidnum; ++i) {
      boids.emplace_back(bs::randVel(), bs::randPos(flock_window_size_d), true);
    }

    sf::ConvexShape non_pred_boid{bs::makeBoidShape(sf::Color::Cyan)};
    sf::ConvexShape pred_boid{bs::makeBoidShape(sf::Color::Red)};
    sf::CircleShape detection_circle{
        bs::makeCircleShape(parameters.detection_rad, sf::Color::Green)};
    sf::CircleShape danger_circle{
        bs::makeCircleShape(parameters.danger_rad, sf::Color::Red)};
    sf::CircleShape cm_circle{bs::makeCenterDot()};

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

    // La suddivisione sarà così, nel main voglio solo load di simulation_params
    // e render_params, poi faccio un conductor.run() e quello fa sì che render
    // si occupi della gestione della finestra (renderstart) e simulation
    // (simulationstart) faccia sì che behaviour(ex vChange) si occupi del
    // calcolo delle velocità e degli spostamenti, tutto sfruttando i metodi di
    // boid, in questa maniera ogni TU contiene correttamente tutte le parti
    // dedicate ad un singolo scopo e non ad un argomento. Devo arrivare a
    // gestire meglio il vettore di boids che chiamerò flock perchè altrimenti
    // com'è ora viene gestito in parte da main e da renderFrame di render, la
    // domanda è, come lo chiamo?
    // sviluppare una TU per statistics

    // Un pelo meglio la divisione in layer:
    // input layer: input e i due config file
    // base/math layer: v2D e rand
    // Simulation_lower:boid
    // Simulation: simulation
    // Render: render
    // Application: conductor

    //  Questo anche lo dovrei aggiungere nel render, relegarlo a quello

  } catch (std::exception const& err) {
    std::cerr << err.what() << "\n";
    return 1;
  }
}
// Controlla se è il distruttore che elimina IoWindow oppure se è la logica
// del programma