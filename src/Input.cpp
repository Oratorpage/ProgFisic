#include "Input.hpp"

#include <iostream>
#include <stdexcept>

namespace flock {
SimParams readparams() {
  SimParams p;

  std::cout << "Input the values for the desired simulation: N: ";
  if (!(std::cin >> p.BoidNum) || p.BoidNum <= 0) {
    throw std::runtime_error("Negative, zero or not integer number of boids");
  }
  std::cout << "s: ";
  if (!(std::cin >> p.s) || p.s <= 0) {
    throw std::runtime_error(
        "Negative or zero value for the separation coefficient");
  }
  std::cout << "a: ";
  if (!(std::cin >> p.a) || p.a <= 0) {
    throw std::runtime_error(
        "Negative or zero value for the alignment coefficient");
  }
  std::cout << "c: ";
  if (!(std::cin >> p.c) || p.c <= 0) {
    throw std::runtime_error(
        "Negative or zero value for the cohesion coefficient");
  }
  std::cout << "detectrad: ";
  if (!(std::cin >> p.detectrad) || p.detectrad <= 0) {
    throw std::runtime_error("Negative or zero value for the detectrad value");
  }
  std::cout << "dangerrad: ";
  if (!(std::cin >> p.dangerrad) || p.dangerrad <= 0) {
    throw std::runtime_error("Negative or zero value for the dangerrad value");
  }
  std::cout << "Toroidal Space active (1 for yes, 0 for no): ";
  if (!(std::cin >> p.toroidal)) {
    throw std::runtime_error("Unvalid value for the Toroidal Space decision");
  }
  std::cout << "Operational Radiuses active (1 for yes, 0 for no): ";
  if (!(std::cin >> p.oprad)) {
    throw std::runtime_error("Unvalid value for the Operational Radiuses decision");
  }

  return p;
}

}  // namespace flock