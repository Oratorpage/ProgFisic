#include "boid.hpp"

#include "doctest.h"

// Boid constructors testing
TEST_CASE("Getters") {
  bs::Boid b{{120., 230.}, {150., 170.}, false};
  CHECK(b.Vel().x == doctest::Approx(120.));
  CHECK(b.Vel().y == doctest::Approx(230.));
  CHECK(b.Pos().x == doctest::Approx(150.));
  CHECK(b.Pos().y == doctest::Approx(170.));
  CHECK(b.IsPredator() == false);
}
TEST_CASE("Setters") {
  bs::Boid b{{120., 230.}, {150., 170.}, false};
  b.setPosition(140., true);
  b.setPosition(10., false);
  CHECK(b.Pos().x == doctest::Approx(140));
  CHECK(b.Pos().y == doctest::Approx(10));
}
TEST_CASE("Update") {
  bs::Boid b{{120., 230.}, {150., 170.}, false};
  double dt{0.1};
  bs::V2D vel_update{1.1, 1.1};
  b.completeUpdate(vel_update, dt);
  CHECK(b.Vel().x == doctest::Approx(121.1).epsilon(0.001));
  CHECK(b.Vel().y == doctest::Approx(231.1).epsilon(0.001));
  CHECK(b.Pos().x == doctest::Approx(162.11).epsilon(0.001));
  CHECK(b.Pos().y == doctest::Approx(193.11).epsilon(0.001));
}
TEST_CASE("Velocity update") {
  bs::Boid b{{100., 130.}, {150., 170.}, false};
  bs::V2D vel_update{1.1, 1.1};
  b.vUpdate(vel_update);
  CHECK(b.Vel().x == doctest::Approx(101.1).epsilon(0.001));
  CHECK(b.Vel().y == doctest::Approx(131.1).epsilon(0.001));
}
TEST_CASE("Limitator upper positive") {
  bs::Boid b{{120., 230.}, {150., 170.}, false};
  double max_speed{250};
  double min_speed{25};
  b.limitVelocity(max_speed, min_speed);
  CHECK(b.Vel().x == doctest::Approx(115.642).epsilon(0.001));
  CHECK(b.Vel().y == doctest::Approx(221.646).epsilon(0.001));
}
TEST_CASE("Limitator upper negative") {
  bs::Boid b{{-120., -230.}, {150., 170.}, false};
  double max_speed{250};
  double min_speed{25};
  b.limitVelocity(max_speed, min_speed);
  CHECK(b.Vel().x == doctest::Approx(-115.642).epsilon(0.001));
  CHECK(b.Vel().y == doctest::Approx(-221.646).epsilon(0.001));
}
TEST_CASE("Limitator lower positive") {
  bs::Boid b{{10., 5.}, {150., 170.}, false};
  double max_speed{250};
  double min_speed{25};
  b.limitVelocity(max_speed, min_speed);
  CHECK(b.Vel().x == doctest::Approx(22.361).epsilon(0.001));
  CHECK(b.Vel().y == doctest::Approx(11.180).epsilon(0.001));
}
TEST_CASE("Limitator lower negative") {
  bs::Boid b{{-10., -5.}, {150., 170.}, false};
  double max_speed{250};
  double min_speed{25};
  b.limitVelocity(max_speed, min_speed);
  CHECK(b.Vel().x == doctest::Approx(-22.361).epsilon(0.001));
  CHECK(b.Vel().y == doctest::Approx(-11.180).epsilon(0.001));
}
