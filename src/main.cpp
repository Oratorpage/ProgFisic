#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "conductor.hpp"
#include "input.hpp"

// char* argv[] o char** argv? So che sono dati diversi, ma in pratatica quali
// sono gli use-cases?
int main(int argc, char** argv) {
  try {
    if (argc < 2) {
      throw std::runtime_error{"No configurational file selected"};
    } else if (argc > 3) {
      throw std::runtime_error{"Too many arguments"};
    }

    // Qua va cambiato readSimulationParams per prendere char** argv o char*
    // argv[] e soprattutto che dia come output configuration
    bs::Config configuration{bs::readParams(argv[1])};

    double time_factor{1.};

    if (argc == 3) {
      time_factor = 0.;
    }

    bs::Conductor application{configuration, time_factor};

    application.start();
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
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
    /////////////////////////////////////////////////////////////////////////

  } catch (std::exception const& err) {
    std::cerr << err.what() << "\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Unknown exception found \n";
    return EXIT_FAILURE;
  }
}