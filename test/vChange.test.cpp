#include "vChange.hpp"

#include "doctest.h"
#include "simParams.hpp"

// atan2 works with "IEEE floating-point arithmetic (IEC 60559)" as per
// cppreference so I implemented complimentary to the horizon the limit handling
// to be correct

// Test on known angles R = 1

// Both the velocity coordinates are zero, I decided to have a standard 0
// angle for now, it depends on the update of the velocity I'll implement later
TEST_CASE(" Test normGammaHorizon (/°)") {
  flock::Boid bi{{0., 0.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 0.);
}

// Border fourth - first quadrant
TEST_CASE(" Test normGammaHorizon (0°)") {
  flock::Boid bi{{1., 0.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 0.);
}
// First quadrant
TEST_CASE(" Test normGammaHorizon (30°)") {
  flock::Boid bi{{0.8660, -0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 30.);
}
TEST_CASE(" Test normGammaHorizon (33°)") {
  flock::Boid bi{{0.8387, -0.5446}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 33.);
}
TEST_CASE(" Test normGammaHorizon (45°)") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
}
TEST_CASE(" Test normGammaHorizon (53°)") {
  flock::Boid bi{{0.6018, -0.7986}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 53.);
}
TEST_CASE(" Test normGammaHorizon (60°)") {
  flock::Boid bi{{0.5, -0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 60.);
}
// Border first - second quadrant
TEST_CASE(" Test normGammaHorizon (90°)") {
  flock::Boid bi{{0., -1.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 90.);
}
// Second quadrant
TEST_CASE(" Test normGammaHorizon (120°)") {
  flock::Boid bi{{-0.5, -0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 120.);
}
TEST_CASE(" Test normGammaHorizon (121°)") {
  flock::Boid bi{{-0.5150, -0.8572}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 121.);
}
TEST_CASE(" Test normGammaHorizon (135°)") {
  flock::Boid bi{{-0.7071, -0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 135.);
}
TEST_CASE(" Test normGammaHorizon (150°)") {
  flock::Boid bi{{-0.8660, -0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 150.);
}
TEST_CASE(" Test normGammaHorizon (173°)") {
  flock::Boid bi{{-0.9925, -0.1219}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 173.);
}
// Border second - third quadrant
TEST_CASE(" Test normGammaHorizon (180°)") {
  flock::Boid bi{{-1, 0.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 180.);
}
// Third quadrant
TEST_CASE(" Test normGammaHorizon (210°)") {
  flock::Boid bi{{-0.8660, 0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 210.);
}
TEST_CASE(" Test normGammaHorizon (225°)") {
  flock::Boid bi{{-0.7071, 0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 225.);
}
TEST_CASE(" Test normGammaHorizon (228°)") {
  flock::Boid bi{{-0.6691, 0.7431}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 228.);
}
TEST_CASE(" Test normGammaHorizon (240)") {
  flock::Boid bi{{-0.5, 0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 240.);
}
TEST_CASE(" Test normGammaHorizon (264)") {
  flock::Boid bi{{-0.1045, 0.9945}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 264.);
}
// Border third - fourth quadrant
TEST_CASE(" Test normGammaHorizon (270°)") {
  flock::Boid bi{{0., 1.}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 270.);
}
// Fourth quadrant
TEST_CASE(" Test normGammaHorizon (300°)") {
  flock::Boid bi{{0.5, 0.8660}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 300.);
}
TEST_CASE(" Test normGammaHorizon (308°)") {
  flock::Boid bi{{0.6157, 0.7880}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 308.);
}
TEST_CASE(" Test normGammaHorizon (315°)") {
  flock::Boid bi{{0.7071, 0.7071}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 315.);
}
TEST_CASE(" Test normGammaHorizon (330°)") {
  flock::Boid bi{{0.8660, 0.5}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 330.);
}
TEST_CASE(" Test normGammaHorizon (345°)") {
  flock::Boid bi{{0.9659, 0.2588}, {100., 100.}};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 345.);
}

// Testing normAngHorizon
// I chose bi-bj to mantain coherence with the sfml plain, otherwise there would
// be incongruences

// Both the position coordinates are zero, I decided to have a standard 0
// angle, for now, it depends on the update of the velocity I'll implement later
TEST_CASE(" Test normAngHorizon (/)") {
  flock::Boid bi{{0., 0.}, {100., 100.}};
  flock::Boid bj{{0., 0.}, {100., 100.}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 0.);
}

// Test on known angles R = 25
// Border fourth - first quadrant bi-bj(-25,0) bj-bi(25,0)
TEST_CASE(" Test normAngHorizon (0°)") {
  flock::Boid bi{{0.1, 0.}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {125., 100.}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 0.);
}
// First quadrant
//                                            bj-bi(23.9076,-7.3093)
TEST_CASE(" Test normAngHorizon (17°)") {
  flock::Boid bi{{0.8660, -0.5}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {123.9076, 92.6907}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 17.);
}
//                    bi-bj (-21.6506,12.5) bj-bi (21.6506,-12.5)
TEST_CASE(" Test normAngHorizon (30°)") {
  flock::Boid bi{{0.1, 0.1}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {121.6506, 87.5}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 30.);
}
//                bi-bj (-17.6777,17.6777) bj-bi (17.6777,-17.6777)
TEST_CASE(" Test normAngHorizon (45°)") {
  flock::Boid bi{{0.7071, 0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {117.6777, 82.3223}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 45.);
}
//                bi-bj (-12.5,21.6506) bj-bi (12.5,-21.6506)
TEST_CASE(" Test normAngHorizon (60°)") {
  flock::Boid bi{{0.5, 0.8660}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {112.5, 78.3494}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 60.);
}
//                                            bj-bi(3.0467,-24.8137)
TEST_CASE(" Test normAngHorizon (83°)") {
  flock::Boid bi{{0.8660, -0.5}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {103.0467, 75.1863}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 83.);
}
// Border first - second quadrant bi-bj(0,25) bj-bi(0,-25)
TEST_CASE(" Test normAngHorizon (90°)") {
  flock::Boid bi{{0., 0.1}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {100., 75.}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 90.);
}
//                                            bj-bi(-8.9592,-23.3395)
TEST_CASE(" Test normAngHorizon (111°)") {
  flock::Boid bi{{0., 0.1}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {91.0408, 76.6605}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 111.);
}
// Second quadrant                            bj-bi(-12.5,-21.6505)
TEST_CASE(" Test normAngHorizon (120°)") {
  flock::Boid bi{{-0.5, 0.8660}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {87.5, 78.3494}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 120.);
}
//                                            bj-bi(-17.6777,-17.6777)
TEST_CASE(" Test normAngHorizon (135°)") {
  flock::Boid bi{{-0.7071, 0.7071}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {82.3223, 82.3223}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 135.);
}
//                                            bj-bi(-19.9659,-15.0454)
TEST_CASE(" Test normAngHorizon (143°)") {
  flock::Boid bi{{-0.7071, 0.7071}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {80.0341, 84.9546}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 143.);
}
//                                            bj-bi(-21.6505,-12.5)
TEST_CASE(" Test normAngHorizon (150°)") {
  flock::Boid bi{{-0.8660, 0.5}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {78.3494, 87.5}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 150.);
}
// Border second - third quadrant bi-bj(25,0) bj-bi(-25,0)
TEST_CASE(" Test normAngHorizon (180°)") {
  flock::Boid bi{{-0.1, 0.}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {75., 100.}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 180.);
}
// Third quadrant                             bj-bi(-21.6506,12.5)
TEST_CASE(" Test normAngHorizon (210°)") {
  flock::Boid bi{{-0.8660, -0.5}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {78.3494, 112.5}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 210.);
}
//                                            bj-bi(-20.7259,13.9798)
TEST_CASE(" Test normAngHorizon (214°)") {
  flock::Boid bi{{-0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {79.2741, 113.9798}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 214.);
}
//                                            bj-bi(-17.6777,17.6777)
TEST_CASE(" Test normAngHorizon (225°)") {
  flock::Boid bi{{-0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {82.3223, 117.6777}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 225.);
}
//                                            bj-bi(-12.5,21.6505)
TEST_CASE(" Test normAngHorizon (240°)") {
  flock::Boid bi{{-0.5, -0.8660}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {87.5, 121.6506}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 240.);
}
//                                            bj-bi(-10.9593,22.4698)
TEST_CASE(" Test normAngHorizon (244°)") {
  flock::Boid bi{{-0.5, -0.8660}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {89.0407, 122.4698}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 244.);
}
// Border third - fourth quadrant bi-bj(0,-25) bj-bi(0,25)
TEST_CASE(" Test normAngHorizon (270°)") {
  flock::Boid bi{{0., -0.1}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {100., 125.}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 270.);
}
//                                            bj-bi(0.8725,24.9848)
TEST_CASE(" Test normAngHorizon (272°)") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {100.8725, 124.9848}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 272.);
}
// Fourth quadrant                            bj-bi(12.5,21.6506)
TEST_CASE(" Test normAngHorizon (300°)") {
  flock::Boid bi{{0.5, -0.8660}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {112.5, 121.6506}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 300.);
}
//                                            bj-bi(17.6777,17.6777)
TEST_CASE(" Test normAngHorizon (315°)") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {117.6777, 117.6777}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 315.);
}
//                                            bj-bi(19.4286,15.7330)
TEST_CASE(" Test normAngHorizon (321°)") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {119.4286, 115.7330}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 321.);
}
//                                            bj-bi(21.6506,12.5)
TEST_CASE(" Test normAngHorizon (330°)") {
  flock::Boid bi{{0.8660, -0.5}, {100., 100.}};
  flock::Boid bj{{0., 0.1}, {121.6506, 112.5}};
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 330.);
}

// Testing angleBoidAdd R=25

TEST_CASE(
    " Test angleBoidAdd gamma{45°}, ang{30°}, params.angle_of_view{40°}") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {121.6506, 87.5}};
  flock::SimParams parameters{100, 0, 20., 3., 5., 55., 23., 40., false, false};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 30.);
  std::vector<flock::Boid*> nearboids;
  flock::angleBoidAdd(bi, bj, parameters, gamma, nearboids);
  CHECK(nearboids.size() != 0);
}
TEST_CASE(
    " Test angleBoidAdd gamma{45°}, ang{60°}, params.angle_of_view{40°}") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {112.5, 78.3494}};
  flock::SimParams parameters{100, 0, 20., 3., 5., 55., 23., 40., false, false};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 60.);
  std::vector<flock::Boid*> nearboids;
  flock::angleBoidAdd(bi, bj, parameters, gamma, nearboids);
  CHECK(nearboids.size() != 0);
}
// On the border
TEST_CASE(
    " Test angleBoidAdd gamma{45°}, ang{25°}, params.angle_of_view{40°}") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {122.6577, 89.4345}};
  flock::SimParams parameters{100, 0, 20., 3., 5., 55., 23., 40., false, false};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 25.);
  std::vector<flock::Boid*> nearboids;
  flock::angleBoidAdd(bi, bj, parameters, gamma, nearboids);
  CHECK(nearboids.size() != 0);
}
TEST_CASE(
    " Test angleBoidAdd gamma{45°}, ang{65°}, params.angle_of_view{40°}") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {110.5654, 77.3423}};
  flock::SimParams parameters{100, 0, 20., 3., 5., 55., 23., 40., false, false};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 65.);
  std::vector<flock::Boid*> nearboids;
  flock::angleBoidAdd(bi, bj, parameters, gamma, nearboids);
  CHECK(nearboids.size() != 0);
}
// Around the world
TEST_CASE(
    " Test angleBoidAdd gamma{45°}, ang{140°}, params.angle_of_view{40°}") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {80.8489, 83.9303}};
  flock::SimParams parameters{100, 0, 20., 3., 5., 55., 23., 40., false, false};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 140.);
  std::vector<flock::Boid*> nearboids;
  flock::angleBoidAdd(bi, bj, parameters, gamma, nearboids);
  CHECK(nearboids.size() == 0);
}
TEST_CASE(
    " Test angleBoidAdd gamma{45°}, ang{240°}, params.angle_of_view{40°}") {
  flock::Boid bi{{0.7071, -0.7071}, {100., 100.}};
  flock::Boid bj{{0.1, 0.1}, {87.5, 121.6506}};
  flock::SimParams parameters{100, 0, 20., 3., 5., 55., 23., 40., false, false};
  double gamma{flock::normGammaHorizon(bi)};
  CHECK(doctest::Approx(gamma).epsilon(0.0001) == 45.);
  double ang{flock::normAngHorizon(bi, bj)};
  CHECK(doctest::Approx(ang).epsilon(0.0001) == 240.);
  std::vector<flock::Boid*> nearboids;
  flock::angleBoidAdd(bi, bj, parameters, gamma, nearboids);
  CHECK(nearboids.size() == 0);
}