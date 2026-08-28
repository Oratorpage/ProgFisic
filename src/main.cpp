#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "conductor.hpp"
#include "input.hpp"


int main(int argc, char** argv) {
  try {
    if (argc < 2) {
      throw std::runtime_error{"No configuration file selected"};
    } else if (argc > 2/*3*/) {
      throw std::runtime_error{"Too many arguments"};
    }

    
    bs::Config configuration{bs::readParams(argv[1])};

    // double time_factor{1.};

    // if (argc == 3) {
    //   time_factor = 0.;
    // }

    bs::Conductor application{configuration/*, time_factor*/};
    application.start(configuration.rp);

  } catch (std::exception const& err) {
    std::cerr << err.what() << "\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Unknown exception found \n";
    return EXIT_FAILURE;
  }
}