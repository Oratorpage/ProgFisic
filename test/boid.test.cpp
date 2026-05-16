
#include "boid.hpp"

#include "doctest.h"
#include "v2D.hpp"

// Le domande sono due:
// Cosa devo testare a partire dall'hpp? Devo
// testare solo le funzioni membro? Anche i costruttori? Anche le funzioni che
// mi restituiscono solo il parametro privato?
// Inoltre, delle funzioni membro, devo testare tutti i casi possibili, anche
// quelli irrealizzabili con il mio main? anche quelli irrealizzabili per lo
// scopo del programma in sè?

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

 Qua bisogna chiedere se test e struttura delle TU va fatta in maniera tale che
 funzioni anche stand-alone con un main generico come libreria perchè in quel
 caso devo cambiare effettivamente un po' di cose
*/

// Boid update testing
// For all of these tests there is no difference between prey or predator, this
// difference only plays a part when the resulting velocity is calculated so in
// the vChange TU
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

// Update velocity{0., 0.}

TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', "
    "vel_update{0., 0.}") {
  flock::Boid b1{{10., 10.}, {10., 10.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{0., 0.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{20., 20.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{10.333, 10.333};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', "
    "vel_update{0., 0.}") {
  flock::Boid b1{{10., 10.}, {20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{0., 0.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{10., 10.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20.167, 20.167};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// I'm not gonna do the test for every border of the toroidal configuration
// given it works above
TEST_CASE("Boid update - standard predator, toroidal, vel_update{0., 0.}") {
  flock::Boid b1{{-10., -10.}, {-20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{0., 0.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-10., -10.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{799.833, 599.833};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}

// Update velocity is negative

TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', "
    "vel_update is negative") {
  flock::Boid b1{{10., 10.}, {10., 10.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-100., -100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{18.333, 18.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{10.306, 10.306};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', "
    "vel_update is negative") {
  flock::Boid b1{{10., 10.}, {20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-100., -100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{8.333, 8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20.139, 20.139};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// I'm not gonna do the test for every border of the toroidal configuration
// given it works above
TEST_CASE("Boid update - standard predator, toroidal, vel_update is negative") {
  flock::Boid b1{{-10., -10.}, {-20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-100., -100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-11.667, -11.667};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{799.806, 599.806};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}

/* Testing that the velocity limiter behaves according to expectations in the
 * cases where the velocity is bigger that the maximum before or after the
 * update, for both the positive and negative limits
 *
 * For the non_toroidal cases max_speed is 250.
 * For the toroidal cases max_speed is 150.
 */

/*                                 AFTER CASE
The initial velocity is smaller than the max_speed but the update increases it,
the limiter should bring it down.
*/
TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', "
    "velocity limiter works - > max vel after update") {
  flock::Boid b1{{249., 249.}, {10., 10.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{250., 250.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{14.168, 14.168};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// Negative velocity
// The negative velocity gets lowered even earlier by the 'wall'
TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', "
    "velocity limiter works - > max vel after update  - negative") {
  flock::Boid b1{{-249., -249.}, {10., 10.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-1000., -1000.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{-250., -250.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{5.832, 5.832};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', "
    "velocity limiter works - > max vel after update") {
  flock::Boid b1{{249., 249.}, {20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{250., 250.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{24.168, 24.168};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// Negative velocity
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', "
    "velocity limiter works - > max vel after update - negative") {
  flock::Boid b1{{-249., -249.}, {20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-100., -100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-250., -250.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{15.832, 15.832};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// I'm not gonna do the test for every border of the toroidal configuration
// given it works above
TEST_CASE(
    "Boid update - standard predator, toroidal, velocity limiter works - > max "
    "vel after update") {
  flock::Boid b1{{149., 149.}, {820., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{150., 150.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{2.5005, 2.5005};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// Negative velocity
TEST_CASE(
    "Boid update - standard predator, toroidal, velocity limiter works - > max "
    "vel after update - negative") {
  flock::Boid b1{{-149., -149.}, {-20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-100., -100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-150., -150.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{797.500, 597.500};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}

/*                               BEFORE CASE
The case where it has a bigger velocity than the max_speed before the update
is impossible because in the preceding update the limiter should have brought
the velocity down, I'll include it in case somewhere else in the program there
is an error that causes this or if the user decides to create a boid with a
velocity > max_speed
*/
TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', "
    "velocity limiter works - > max vel before update") {
  flock::Boid b1{{260., 260.}, {10., 10.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{250., 250.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{14.168, 14.168};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// Negative velocity
// The negative velocity gets lowered even earlier by the 'wall'
TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', "
    "velocity limiter works - > max vel before update  - negative") {
  flock::Boid b1{{-260., -260.}, {10., 10.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{-248.333, -248.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{5.860, 5.860};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', "
    "velocity limiter works - > max vel before update") {
  flock::Boid b1{{260., 260.}, {20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{250., 250.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{24.168, 24.168};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// Negative velocity
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', "
    "velocity limiter works - > max vel before update - negative") {
  flock::Boid b1{{-260., -260.}, {20., 20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-250., -250.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{15.832, 15.832};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// I'm not gonna do the test for every border of the toroidal configuration
// given it works above
TEST_CASE(
    "Boid update - standard predator, toroidal, velocity limiter works - > max "
    "vel before update") {
  flock::Boid b1{{160., 160.}, {820., 620.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-100., -100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{150., 150.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{2.5005, 2.5005};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// Negative velocity
TEST_CASE(
    "Boid update - standard predator, toroidal, velocity limiter works - > max "
    "vel before update - negative") {
  flock::Boid b1{{-160., -160.}, {-20., -20.}, true};
  double dt{0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{-100., -100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-150., -150.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{797.500, 597.500};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}

/*These tests are only to ensure total functioning in case of weird problems, in
 * no part of the simulations these situations would be encountered. Are they
 * necessary if they only ensure regardless functionality or they can be
 * ommitted based on the main i designed?
 */
//(dt = 0)

TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', time is "
    "zero") {
  flock::Boid b1{{10., 10.}, {10., 10.}, true};
  double dt{0.};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{20., 20.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{10., 10.};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', time is "
    "zero") {
  flock::Boid b1{{10., 10.}, {20., 20.}, true};
  double dt{0.};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{10., 10.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{20., 20.};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// I'm not gonna do the test for every border of the toroidal configuration
// given it works above
TEST_CASE("Boid update - standard predator, toroidal, time is zero") {
  flock::Boid b1{{-10., -10.}, {-20., -20.}, true};
  double dt{0.};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-10., -10.};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{800., 600.};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}

//(dt < 0)

TEST_CASE(
    "Boid update - standard predator, non toroidal, behind 'wall', negative "
    "time") {
  flock::Boid b1{{10., 10.}, {10., 10.}, true};
  double dt{-0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);
  flock::V2D result_ipo_vel{18.333, 18.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{9.694, 9.694};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
TEST_CASE(
    "Boid update - standard predator, non toroidal, ahead of 'wall', negative "
    "time") {
  flock::Boid b1{{10., 10.}, {20., 20.}, true};
  double dt{-0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{false};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{8.333, 8.333};
  flock::V2D result_real_vel{b1.Vel()};
  CHECK(
      (result_ipo_vel.x == doctest::Approx(result_real_vel.x).epsilon(0.0001)));
  CHECK(
      (result_ipo_vel.y == doctest::Approx(result_real_vel.y).epsilon(0.0001)));

  flock::V2D result_ipo_pos{19.861, 19.861};
  flock::V2D result_real_pos{b1.Pos()};
  CHECK(
      (result_ipo_pos.x == doctest::Approx(result_real_pos.x).epsilon(0.0001)));
  CHECK(
      (result_real_pos.y == doctest::Approx(result_ipo_pos.y).epsilon(0.0001)));
}
// I'm not gonna do the test for every border of the toroidal configuration
// given it works above
TEST_CASE("Boid update - standard predator, toroidal, negative time") {
  flock::Boid b1{{-10., -10.}, {-20., -20.}, true};
  double dt{-0.01667};
  flock::V2D flock_window_size{800., 600.};
  flock::V2D vel_update{100., 100.};
  bool toroidal{true};
  b1.update(dt, flock_window_size, vel_update, toroidal);

  flock::V2D result_ipo_vel{-11.667, -11.667};
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
