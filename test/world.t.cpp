#include "world.hpp"

#include "doctest.h"

TEST_CASE("Class invariant") {
  bs::WorldParams wp1{{800, 600}, true};
  bs::WorldParams wp2{{800, -1}, false};
  bs::WorldParams wp3{{0, -1}, true};

  CHECK_NOTHROW(bs::World{wp1});
  CHECK_THROWS(bs::World{wp2});
  CHECK_THROWS(bs::World{wp3});
}
TEST_CASE("Getters") {
  bs::WorldParams wp1{{800, 600}, true};
  bs::World world1{wp1};

  CHECK(world1.getDimensions().x == 800);
  CHECK(world1.getDimensions().y == 600);
  CHECK(world1.getWidth() == 800);
  CHECK(world1.getHeight() == 600);
  CHECK(world1.isToroidal() == true);
}
TEST_CASE("Toroidal wrap") {
  bs::Boid b1{{120., 130.}, {30., 30.}, false};
  bs::Boid b2{{120., 130.}, {-0.1, -10.}, false};
  bs::Boid b3{{120., 130.}, {810., 690.}, false};
  std::vector<bs::Boid> flock{b1, b2, b3};

  bs::WorldParams wp1{{800, 600}, true};
  bs::World world1{wp1};
  world1.wrap(flock);

  CHECK(flock[0].Pos().x == 30.);
  CHECK(flock[0].Pos().y == 30.);
  CHECK(flock[1].Pos().x == 800.);
  CHECK(flock[1].Pos().y == 600.);
  CHECK(flock[2].Pos().x == 0.);
  CHECK(flock[2].Pos().y == 0.);
}
TEST_CASE("containVel") {
  //           velocity     //position  //hunter
  bs::Boid b1{{120., 130.}, {30., 30.}, false};
  bs::Boid b2{{-120., -130.}, {0., -10.}, false};
  bs::Boid b3{{1., 1.}, {1., 1.}, false};
  bs::Boid b4{{120., 130.}, {810., 690.}, false};
  bs::Boid b5{{120., 130.}, {790., 590.}, false};
  bs::BoidProperties bp{90., 30., 280., 250., 25., 0.7, 0.5, 0.3};

  bs::WorldParams wp1{{800, 600}, true};
  bs::World world1{wp1};

  CHECK(world1.containVel(b1, bp).x == 0.);
  CHECK(world1.containVel(b1, bp).y == 0.);
  CHECK(world1.containVel(b2, bp).x == 100.);
  CHECK(world1.containVel(b2, bp).y == 100.);
  CHECK(world1.containVel(b3, bp).x == doctest::Approx(249.987).epsilon(0.001));
  CHECK(world1.containVel(b3, bp).y == doctest::Approx(249.987).epsilon(0.001));
  CHECK(world1.containVel(b4, bp).x == -100.);
  CHECK(world1.containVel(b4, bp).y == -100.);
  CHECK(world1.containVel(b5, bp).x == doctest::Approx(-26.507).epsilon(0.001));
  CHECK(world1.containVel(b5, bp).y == doctest::Approx(-26.632).epsilon(0.001));
}
TEST_CASE("Non-toroidal containment") {
  bs::Boid b1{{120., 130.}, {30., 30.}, false};
  bs::Boid b2{{-120., -130.}, {0., -10.}, false};
  bs::Boid b3{{120., 130.}, {810., 690.}, false};
  bs::Boid b4{{1., 1.}, {1., 1.}, false};
  bs::Boid b5{{120., 130.}, {790., 590.}, false};
  std::vector<bs::Boid> flock{b1, b2, b3, b4, b5};
  bs::BoidProperties bp{90., 30., 280., 250., 25., 0.7, 0.5, 0.3};

  bs::WorldParams wp1{{800, 600}, true};
  bs::World world1{wp1};
  world1.contain(flock, bp);

  CHECK(flock[0].Pos().x == 30.);
  CHECK(flock[0].Pos().y == 30.);
  CHECK(flock[0].Vel().x == 120.);
  CHECK(flock[0].Vel().y == 130.);

  CHECK(flock[1].Pos().x == 0.);
  CHECK(flock[1].Pos().y == -10.);
  CHECK(flock[1].Vel().x == -20.);
  CHECK(flock[1].Vel().y == -30.);

  CHECK(flock[2].Pos().x == 810.);
  CHECK(flock[2].Pos().y == 690.);
  CHECK(flock[2].Vel().x == 20.);
  CHECK(flock[2].Vel().y == 30.);

  CHECK(flock[3].Pos().x == 1.);
  CHECK(flock[3].Pos().y == 1.);
  CHECK(flock[3].Vel().x == doctest::Approx(250.987).epsilon(0.001));
  CHECK(flock[3].Vel().y == doctest::Approx(250.987).epsilon(0.001));

  CHECK(flock[4].Pos().x == 790.);
  CHECK(flock[4].Pos().y == 590.);
  CHECK(flock[4].Vel().x == doctest::Approx(93.493).epsilon(0.001));
  CHECK(flock[4].Vel().y == doctest::Approx(103.368).epsilon(0.001));
}