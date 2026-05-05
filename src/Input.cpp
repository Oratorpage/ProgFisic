#include "Input.hpp"

#include <iostream>
#include <stdexcept>

namespace flock {
SimParams readParams() {
  SimParams p;

  std::cout << "Input the values for the desired simulation: \n"
            << "Number of non predator boids: ";
  if (!(std::cin >> p.non_pred_boidnum) || p.non_pred_boidnum < 0) {
    throw std::runtime_error(
        "Negative, or not integer number of non predator boids");
  }
  std::cout << "Number of predator boids: ";
  if (!(std::cin >> p.pred_boidnum) || p.pred_boidnum < 0) {
    throw std::runtime_error(
        "Negative, or not integer number of predator boids");
  }
  std::cout << "separation coefficient: ";
  if (!(std::cin >> p.s) || p.s <= 0) {
    throw std::runtime_error(
        "Negative or zero value for the separation coefficient");
  }
  std::cout << "alignment coefficient: ";
  if (!(std::cin >> p.a) || p.a <= 0) {
    throw std::runtime_error(
        "Negative or zero value for the alignment coefficient");
  }
  std::cout << "cohesion coefficient: ";
  if (!(std::cin >> p.c) || p.c <= 0) {
    throw std::runtime_error(
        "Negative or zero value for the cohesion coefficient");
  }
  std::cout << "radius of detection: ";
  if (!(std::cin >> p.detection_rad) || p.detection_rad <= 0) {
    throw std::runtime_error("Negative or zero value for the detectrad value");
  }
  std::cout << "radius of danger: ";
  if (!(std::cin >> p.danger_rad) || p.danger_rad <= 0) {
    throw std::runtime_error("Negative or zero value for the dangerrad value");
  }
  std::cout << "Toroidal Space active (1 for yes, 0 for no): ";
  if (!(std::cin >> p.toroidal)) {
    throw std::runtime_error("Unvalid value for the Toroidal Space decision");
  }
  std::cout << "Operational Radiuses active (1 for yes, 0 for no): ";
  if (!(std::cin >> p.op_rad)) {
    throw std::runtime_error(
        "Unvalid value for the Operational Radiuses decision");
  }

  return p;
}

}  // namespace flock