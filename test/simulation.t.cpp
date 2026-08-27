#include "simulation.hpp"

#include "doctest.h"

TEST_CASE("buildFlock") {
  bs::WorldParams wp1{{800., 600.}, false};
  bs::BoidProperties bp1{90., 30., 280., 250., 25., 0.7, 0.5, 0.3};
  bs::SimParams sp1{100, 20, 0.01};

  bs::Simulation sim{wp1, bp1, sp1};
  CHECK(sim.currentFlock().size() == 120);
}
TEST_CASE("firstStats") {
  bs::WorldParams wp1{{800., 600.}, false};
  bs::BoidProperties bp1{90., 30., 280., 250., 25., 0.7, 0.5, 0.3};
  bs::SimParams sp1{100, 20, 0.01};

  bs::Simulation sim{wp1, bp1, sp1};
  // These are actually statistics tests so there is a small possibility of
  // these failing, doctest::Approx should reduce this possibility
  CHECK(sim.currentStatistics().cm_pos.x !=
        doctest::Approx(0.).epsilon(0.000001));
  CHECK(sim.currentStatistics().cm_pos.y !=
        doctest::Approx(0.).epsilon(0.000001));
  CHECK(sim.currentStatistics().avg_vel.x !=
        doctest::Approx(0.).epsilon(0.000001));
  CHECK(sim.currentStatistics().avg_vel.y !=
        doctest::Approx(0.).epsilon(0.000001));
  CHECK(sim.currentStatistics().statistics_output != "Invalid");
}
TEST_CASE("Class invariant") {
  bs::WorldParams wp1{{800., 600.}, false};
  bs::WorldParams wp2{{0., 600.}, false};
  bs::BoidProperties bp1{90., 30., 280., 250., 25., 0.7, 0.5, 0.3};
  bs::BoidProperties bp2{30., 90., 280., 250., 25., 0.7, 0.5, 0.3};
  bs::BoidProperties bp3{90., 30., 361., 250., 25., 0.7, 0.5, 0.3};
  bs::SimParams sp1{100, 20, 0.01};
  bs::SimParams sp2{100, 20, -0.01};

  CHECK_NOTHROW(bs::Simulation{wp1, bp1, sp1});
  CHECK_THROWS(bs::Simulation{wp2, bp1, sp1});
  CHECK_THROWS(bs::Simulation{wp1, bp2, sp1});
  CHECK_THROWS(bs::Simulation{wp1, bp1, sp2});
  CHECK_THROWS(bs::Simulation{wp1, bp3, sp1});
}
TEST_CASE("Getters") {
  bs::WorldParams wp1{{800., 600.}, false};
  bs::BoidProperties bp1{90., 30., 280., 250., 25., 0.7, 0.5, 0.3};
  bs::SimParams sp1{100, 20, 0.01};

  bs::Simulation sim{wp1, bp1, sp1};
  CHECK(sim.currentWorld().getDimensions().x == 800.);
  CHECK(sim.currentWorld().getDimensions().y == 600);
  CHECK(sim.currentWorld().isToroidal() == false);

  CHECK(sim.boidProperties().detection_radius == 90.);
  CHECK(sim.boidProperties().danger_radius == 30.);
  CHECK(sim.boidProperties().angle_of_view == 280.);
  CHECK(sim.boidProperties().max_speed == 250.);
  CHECK(sim.boidProperties().min_speed == 25.);
  CHECK(sim.boidProperties().separation == 0.7);
  CHECK(sim.boidProperties().alignment == 0.5);
  CHECK(sim.boidProperties().cohesion == 0.3);

  CHECK(sim.currentFlock().size() == 120);
  CHECK(sim.getSimdt() == 0.01);
}
// Devo fare anche il test di tick? come lo faccio?