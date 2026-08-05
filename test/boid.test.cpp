
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
  bs::Boid b{{10., 10.}, {20., 20.}, false};
  CHECK(b.Vel().x == 0.);
  CHECK(b.Vel().y == 0.);
  CHECK(b.Pos().x == 0.);
  CHECK(b.Pos().y == 0.);
  CHECK(b.IsPredator() == false);
}
TEST_CASE("Boid initialization - constructor with velocity and position") {
  bs::Boid b{{10., 10.}, {20., 20.}, false};
  CHECK(b.Vel().x == 10.);
  CHECK(b.Vel().y == 10.);
  CHECK(b.Pos().x == 20.);
  CHECK(b.Pos().y == 20.);
  CHECK(b.IsPredator() == false);
}
TEST_CASE(
    "Boid initialization - constructor with velocity, position and pred") {
  bs::Boid b{{10., 10.}, {20., 20.}, false};
  CHECK(b.Vel().x == 10.);
  CHECK(b.Vel().y == 10.);
  CHECK(b.Pos().x == 20.);
  CHECK(b.Pos().y == 20.);
  CHECK(b.IsPredator() == false);
}
TEST_CASE("Boid initialization - complete constructor with bad values") {
  bs::Boid b{{10., 10.}, {20., 20.}, false};
  CHECK(b.Vel().x == 10.);
  CHECK(b.Vel().y == 10.);
  CHECK(b.Pos().x == 20.);
  CHECK(b.Pos().y == 20.);
  CHECK(b.IsPredator() != 0.2);
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
