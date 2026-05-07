#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boid.hpp"

#include "doctest.h"
#include "v2D.hpp"

// Boid constructors testing
TEST_CASE("Boid initialization - standard constructor") {
  flock::Boid b{};
  CHECK(b.Vel().x == 0.);
  CHECK(b.Vel().y == 0.);
  CHECK(b.Pos().x == 0.);
  CHECK(b.Pos().y == 0.);
  CHECK(b.IsPred() == false);
}
TEST_CASE("Boid initialization - constructor with velocity and position") {
  flock::Boid b{{10., 10.}, {20., 20.}};
  CHECK(b.Vel().x == 10.);
  CHECK(b.Vel().y == 10.);
  CHECK(b.Pos().x == 20.);
  CHECK(b.Pos().y == 20.);
  CHECK(b.IsPred() == false);
}
TEST_CASE(
    "Boid initialization - constructor with velocity, position and pred") {
  flock::Boid b{{10., 10.}, {20., 20.}, false};
  CHECK(b.Vel().x == 10.);
  CHECK(b.Vel().y == 10.);
  CHECK(b.Pos().x == 20.);
  CHECK(b.Pos().y == 20.);
  CHECK(b.IsPred() == false);
}
TEST_CASE("Boid initialization - complete constructor with bad values") {
  flock::Boid b{{10., 10.}, {20., 20.}, false};
  CHECK(b.Vel().x == 10.);
  CHECK(b.Vel().y == 10.);
  CHECK(b.Pos().x == 20.);
  CHECK(b.Pos().y == 20.);
  CHECK(b.IsPred() != 0.2);
}
/* No bad values can be introduced for a boid initialization, any value that
 doesn't produce compilation errors is acceptable, if it is far from the
 window or if it has the speed of a photon it's not a problem.

 If it is far (in any direction)(and not in toroidal mode) it will be back
 thanks to the update member function and the velocity update; if it is in
 toroidal mode it will just go back to a border in the next update.

 For the velocity it is regulated by the update member function.

 It may have an initial wrong position for the first few milliseconds but
 considering how the user is not prompted to initialize any singular boids it
 shouldn't be a problem, it wouldn't be even with the manual insertion since the
 only thing the user can decide would be the position (by clicking inside the
 window).
*/

// Boid update testing
// For these there is no difference between prey or predator, it is only the
// update not the vChange
TEST_CASE("Boid update - standard predator, non toroidal, behind 'wall'") {
  flock::Boid b1{{10., 10.}, {10., 10.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{21.667, 21.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.001)));

  flock::V2D result_ipo_pos{10.361, 10.361};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.001)));
}
TEST_CASE("Boid update - standard predator, non toroidal, ahead of 'wall'") {
  flock::Boid b1{{10., 10.}, {20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.001)));

  flock::V2D result_ipo_pos{20.194, 20.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.001)));
}
/*-------------------------------------TOROIDAL---------------------------------------

                      __________________________________________
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                      __________________________________________


*-------------------------------------------------------------------------------------
*/
TEST_CASE(
    "Boid update - standard predator, toroidal, befor window borders "
    "left-down") {
  flock::Boid b1{{10., 10.}, {-20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.001)));

  flock::V2D result_ipo_pos{800., 600.};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.001)));
}
TEST_CASE(
    "Boid update - standard predator, toroidal, before window borders "
    "left - ok height") {
  flock::Boid b1{{10., 10.}, {-20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.001)));

  flock::V2D result_ipo_pos{800., 20.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.001)));
}
TEST_CASE(
    "Boid update - standard predator, toroidal, after window borders "
    "ok side - down") {
  flock::Boid b1{{10., 10.}, {20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.001)));

  flock::V2D result_ipo_pos{20.194, 600.};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.001)));
}
//--------------------------------------------------------------------------------
TEST_CASE(
    "Boid update - standard predator, toroidal, before window borders "
    "ok side - up") {
  flock::Boid b1{{10., 10.}, {20., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.001)));

  flock::V2D result_ipo_pos{20.194, 0.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.001)));
}
TEST_CASE(
    "Boid update - standard predator, toroidal, before window borders "
    "ok side - up") {
  flock::Boid b1{{10., 10.}, {20., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.001)));

  flock::V2D result_ipo_pos{20.194, 0.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.001)));
}

// TEST_CASE("Boid update - time is negative") {}
// TEST_CASE("Boid update - vel_update is zero") {}
// TEST_CASE("Boid update - vel_update is negative") {}
// TEST_CASE("Boid update - toroidal is weird") {}