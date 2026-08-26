
#include "boid.hpp"

#include "doctest.h"
#include "v2D.hpp"

// Boid constructors testing
TEST_CASE("Getters"){
     bs::Boid b{{120.,230.},{150.,170.},false};
     CHECK(b.Vel().x == doctest::Approx(120.));
     CHECK(b.Vel().x == doctest::Approx(230.));
     CHECK(b.Pos().x == doctest::Approx(150.));
     CHECK(b.Pos().y == doctest::Approx(170.));
     CHECK(b.IsPredator() == false);
}
TEST_CASE("Setters"){
     bs::Boid b{{120.,230.},{150.,170.},false};
     b.setPosition(140.,true);
     b.setPosition(10.,false);
     CHECK(b.Pos().x == doctest::Approx(140));
     CHECK(b.Pos().x == doctest::Approx(140));
}
//Limitatore con positivi e con negativi
//Updates