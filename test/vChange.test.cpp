#include "vChange.hpp"

#include "doctest.h"

// Ok atan2 works with "IEEE floating-point arithmetic (IEC 60559)" as per
// cppreference, with this it actually works, the problem is with both zeros for
// now
// Limit cases
// Border first - second quadrant
TEST_CASE(" Test normGammaHorizon - v.x == 0 && v.y > 0.") {
  flock::Boid bi{{0., 0.1}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(gamma == 90.);
}
// Border second - third quadrant
TEST_CASE(" Test normGammaHorizon - v.x < 0 && v.y == 0.") {
  flock::Boid bi{{-0.1, 0.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(gamma == 180.);
}
// Border third - fourth quadrant
TEST_CASE(" Test normGammaHorizon - v.x == 0 && v.y < 0.") {
  flock::Boid bi{{0., -0.1}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(gamma == 270.);
}
// Border fourth - first quadrant
TEST_CASE(" Test normGammaHorizon - v.x > 0 && v.y == 0.") {
  flock::Boid bi{{0.1, 0.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(gamma == 0.);
}
// Both the velocity coordinates are zero, I decided to have a standard 0
// angle
TEST_CASE(" Test normGammaHorizon - v.x == 0 && v.y == 0.") {
  flock::Boid bi{{0., 0.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(gamma == 0.);
}
// Test on known angles R = 1
// First quadrant
TEST_CASE(" Test normGammaHorizon - v.x > 0 && v.y > 0.") {
  flock::Boid bi{{0.8660, 0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 30.);
}
TEST_CASE(" Test normGammaHorizon - v.x > 0 && v.y > 0.") {
  flock::Boid bi{{0.7071, 0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
}
TEST_CASE(" Test normGammaHorizon - v.x > 0 && v.y > 0.") {
  flock::Boid bi{{0.5, 0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 60.);
}
// Second quadrant
TEST_CASE(" Test normGammaHorizon - v.x < 0 && v.y > 0.") {
  flock::Boid bi{{-0.5, 0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 120.);
}
TEST_CASE(" Test normGammaHorizon - v.x < 0 && v.y > 0.") {
  flock::Boid bi{{-0.7071, 0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 135.);
}
TEST_CASE(" Test normGammaHorizon - v.x < 0 && v.y > 0.") {
  flock::Boid bi{{-0.8660, 0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 150.);
}
// Third quadrant
TEST_CASE(" Test normGammaHorizon - v.x < 0 && v.y < 0.") {
  flock::Boid bi{{-0.8660, -0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 210.);
}
TEST_CASE(" Test normGammaHorizon - v.x < 0 && v.y < 0.") {
  flock::Boid bi{{-0.7071, -0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 225.);
}
TEST_CASE(" Test normGammaHorizon - v.x < 0 && v.y < 0.") {
  flock::Boid bi{{-0.5, -0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 240.);
}
// Fourth quadrant
TEST_CASE(" Test normGammaHorizon - v.x > 0 && v.y < 0.") {
  flock::Boid bi{{0.5, -0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 300.);
}
TEST_CASE(" Test normGammaHorizon - v.x > 0 && v.y < 0.") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 315.);
}
TEST_CASE(" Test normGammaHorizon - v.x > 0 && v.y < 0.") {
  flock::Boid bi{{0.8660, -0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 330.);
}

// Testing normAngHorizon
// I chose bi-bj to mantain coherence with the sfml plain, more understandable

// FIXA! IL PIANO IN SFML è AL CONTRARIO QUINDI DEVI MODIFICARE LE POSIZIONI
// COERENTEMENTE SE NO QUANDO VAI A CALCOLARLO DAVVERO NEL PIANO NON FUNZIONA

// Limit cases
// Border second - third quadrant bi-bj(25,0) bj-bi(-25,0)
TEST_CASE(" Test normAngHorizon (2)") {
  flock::Boid bi{{-0.1, 0.}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {75., 100.}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(gamma == 180.);
}
// Border third - fourth quadrant bi-bj(0,-25) bj-bi(0,25)
TEST_CASE(" Test normAngHorizon (3)") {
  flock::Boid bi{{0., -0.1}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {100., 125.}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(gamma == 270.);
}

// Both the velocity coordinates are zero, I decided to have a standard 0
// angle
TEST_CASE(" Test normAngHorizon (/)") {
  flock::Boid bi{{0., 0.}, {100., 100.}};
  flock::Boid bj{{0., 0.}, {100., 100.}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(gamma == 0.);
}
// Test on known angles R = 25
// Border fourth - first quadrant bi-bj(-25,0) bj-bi(25,0)
TEST_CASE(" Test normAngHorizon (0°)") {
  flock::Boid bi{{0.1, 0.}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {125., 100.}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(gamma == 0.);
}
// First quadrant bi-bj (-21.6506,12.5) bj-bi (21.6506,-12.5)
TEST_CASE(" Test normAngHorizon (30°)") {
  flock::Boid bi{{0.1, 0.1}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {121.6506, 87.5}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 30.);
}
//                bi-bj (-17.6777,17.6777) bj-bi (17.6777,-17.6777)
TEST_CASE(" Test normAngHorizon (45°)") {
  flock::Boid bi{{0.7071, 0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {117.6777, 82.3223}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
}
//                bi-bj (-12.5,21.6506) bj-bi (12.5,-21.6506)
TEST_CASE(" Test normAngHorizon (60°)") {
  flock::Boid bi{{0.5, 0.8660}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {112.5, 78.3494}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 60.);
}
// Border first - second quadrant bi-bj(0,25) bj-bi(0,-25)
TEST_CASE(" Test normAngHorizon (1)") {
  flock::Boid bi{{0., 0.1}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {100., 75.}};
  double gamma{flock::normAngHorizon(bi, bj)};
  CHECK(gamma == 90.);
}
// // Second quadrant
// TEST_CASE(" Test normAngHorizon - v.x < 0 && v.y > 0.") {
//   flock::Boid bi{{-0.5, 0.8660}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 120.);
// }
// TEST_CASE(" Test normAngHorizon - v.x < 0 && v.y > 0.") {
//   flock::Boid bi{{-0.7071, 0.7071}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 135.);
// }
// TEST_CASE(" Test normAngHorizon - v.x < 0 && v.y > 0.") {
//   flock::Boid bi{{-0.8660, 0.5}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 150.);
// }
// // Third quadrant
// TEST_CASE(" Test normAngHorizon - v.x < 0 && v.y < 0.") {
//   flock::Boid bi{{-0.8660, -0.5}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 210.);
// }
// TEST_CASE(" Test normAngHorizon - v.x < 0 && v.y < 0.") {
//   flock::Boid bi{{-0.7071, -0.7071}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 225.);
// }
// TEST_CASE(" Test normAngHorizon - v.x < 0 && v.y < 0.") {
//   flock::Boid bi{{-0.5, -0.8660}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 240.);
// }
// // Fourth quadrant
// TEST_CASE(" Test normAngHorizon - v.x > 0 && v.y < 0.") {
//   flock::Boid bi{{0.5, -0.8660}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 300.);
// }
// TEST_CASE(" Test normAngHorizon - v.x > 0 && v.y < 0.") {
//   flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 315.);
// }
// TEST_CASE(" Test normAngHorizon - v.x > 0 && v.y < 0.") {
//   flock::Boid bi{{0.8660, -0.5}, {100., 100.}};
//   double gamma{flock::normAngHorizon(bi)};
//   CHECK(doctest::Approx(gamma).epsilon(0.0001) == 330.);
// }
