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
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{10.361, 10.361};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
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
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20.194, 20.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
/*-------------------------------------TOROIDAL---------------------------------------
                                         (e)
                (a)   __________________________________________   (f)
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                (b)  |               flock_window               |  (g)
                     |                                          |
                     |                                          |
                     |                                          |
                     |                                          |
                (c)   __________________________________________   (h)

                                         (d)
*-------------------------------------------------------------------------------------
*/
//(a)
TEST_CASE("Boid update - standard predator, toroidal, case (a)") {
  flock::Boid b1{{-10., -10.}, {-20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-8.333, -8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));
    //Qua c'è un problema perchè io il calcolo l'ho fatto con un'altro valore e ritorna uguale quindi bho
  flock::V2D result_ipo_pos{799.861, 599.861};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(b)
TEST_CASE("Boid update - standard predator, toroidal, case (b)") {
  flock::Boid b1{{-10., 0.}, {-20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-8.333, 1.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{799.861, 20.028};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(c)
TEST_CASE("Boid update - standard predator, toroidal, case (c)") {
  flock::Boid b1{{-10., 10.}, {-20., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-8.333, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{799.861, 0.1945};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(d)
TEST_CASE("Boid update - standard predator, toroidal, case(d)") {
  flock::Boid b1{{0., 10.}, {20., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{1.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20.028, 0.1945};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(e)
TEST_CASE("Boid update - standard predator, toroidal, case (e)") {
  flock::Boid b1{{0., -10.}, {20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{1.667, -8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20.028, 599.861};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(f)
TEST_CASE("Boid update - standard predator, toroidal, case (f)") {
  flock::Boid b1{{10., -10.}, {820., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, -8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{0.1945, 599.861};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(g)
TEST_CASE("Boid update - standard predator, toroidal, case (g)") {
  flock::Boid b1{{10., 0.}, {820., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 1.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{0.1945, 20.028};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(h)
TEST_CASE("Boid update - standard predator, toroidal, case (h)") {
  flock::Boid b1{{10., 10.}, {820., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{0.1945, 0.1945};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
/*Questi test evidenziano come se il boid arriva in una posizione al di fuori
  della finestra con una velocità che non è compatibile con il suo percorso
  precedente (com'è arrivato lì se la sua velocità puntava in un'altra
  direzione complessiva? per esempio in direzione opposta a quella che lo
  collega alla finestra) assumerà temporaneamente di nuovo una posizione
  invalida e nell'aggiornamento successivo
  Dipende in realtà molto da vel_update, se è zero allora al secondo
  aggiornamento non ci sono problemi, altrimenti può creare problemi, tipo
  mantenere attivamente il boid al di fuori della schermata di render
 */
//(a')
TEST_CASE("Boid update - standard predator, toroidal, case (a')") {
  flock::Boid b1{{10., 10.}, {-20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{800.194, 600.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(b')
TEST_CASE("Boid update - standard predator, toroidal, case (b')") {
  flock::Boid b1{{10., 0.}, {-20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, 1.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{800.194, 20.028};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(c')
TEST_CASE("Boid update - standard predator, toroidal, case (c')") {
  flock::Boid b1{{10., -10.}, {-20., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{11.667, -8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{800.194, -0.139};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(d')
TEST_CASE("Boid update - standard predator, toroidal, case(d')") {
  flock::Boid b1{{0., -10.}, {20., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{1.667, -8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20.028, -0.139};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(e')
TEST_CASE("Boid update - standard predator, toroidal, case (e')") {
  flock::Boid b1{{0., 10.}, {20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{1.667, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20.028, 600.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(f')
TEST_CASE("Boid update - standard predator, toroidal, case (f')") {
  flock::Boid b1{{-10., 10.}, {820., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-8.333, 11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{-0.139, 600.194};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(g')
TEST_CASE("Boid update - standard predator, toroidal, case (g')") {
  flock::Boid b1{{-10., 0.}, {820., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-8.333, 1.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{-0.139, 20.028};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
//(h')
TEST_CASE("Boid update - standard predator, toroidal, case (h')") {
  flock::Boid b1{{-10., -10.}, {820., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-8.333, -8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{-0.139, -0.139};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}

// TEST_CASE("Boid update - time is negative") {}
// TEST_CASE("Boid update - vel_update is zero") {}
// TEST_CASE("Boid update - vel_update is negative") {}
// TEST_CASE("Boid update - toroidal is weird") {}