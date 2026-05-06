#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boid.hpp"

#include "doctest.h"

TEST_CASE("Boid update - inizialization") {
  flock::Boid boid1;
  double dt = 0.7;
  CHECK_THROWS(boid1.update(dt, {100., 100.}, {5., 2.}, true));
}
TEST_CASE("Boid update - time is negative") {}
TEST_CASE("Boid update - vel_update is zero") {}
TEST_CASE("Boid update - vel_update is negative") {}
TEST_CASE("Boid update - toroidal is weird") {}