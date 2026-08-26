#include "rand.hpp"

#include "doctest.h"

TEST_CASE("randVel") {
  double max_speed{250.};

  bs::V2D randomvel1{bs::randVel(max_speed)};
  bs::V2D randomvel2{bs::randVel(max_speed)};
  bs::V2D randomvel3{bs::randVel(max_speed)};
  bs::V2D randomvel4{bs::randVel(max_speed)};
  bs::V2D randomvel5{bs::randVel(max_speed)};
  // Needed to separate them like this or I would get a "Expression  Too Complex
  // Please Rewrite As Binary Comparison!"
  CHECK(randomvel1.x < max_speed);
  CHECK(randomvel1.x > -max_speed);
  CHECK(randomvel1.y < max_speed);
  CHECK(randomvel1.y > -max_speed);
  CHECK(randomvel2.x < max_speed);
  CHECK(randomvel2.x > -max_speed);
  CHECK(randomvel2.y < max_speed);
  CHECK(randomvel2.y > -max_speed);
  CHECK(randomvel3.x < max_speed);
  CHECK(randomvel3.x > -max_speed);
  CHECK(randomvel3.y < max_speed);
  CHECK(randomvel3.y > -max_speed);
  CHECK(randomvel4.x < max_speed);
  CHECK(randomvel4.x > -max_speed);
  CHECK(randomvel4.y < max_speed);
  CHECK(randomvel4.y > -max_speed);
  CHECK(randomvel5.x < max_speed);
  CHECK(randomvel5.x > -max_speed);
  CHECK(randomvel5.y < max_speed);
  CHECK(randomvel5.y > -max_speed);
}
TEST_CASE("randPos") {
  bs::V2D world_dimensions{800., 600.};

  bs::V2D randompos1{bs::randPos(world_dimensions)};
  bs::V2D randompos2{bs::randPos(world_dimensions)};
  bs::V2D randompos3{bs::randPos(world_dimensions)};
  bs::V2D randompos4{bs::randPos(world_dimensions)};
  bs::V2D randompos5{bs::randPos(world_dimensions)};

  CHECK(randompos1.x > 0);
  CHECK(randompos1.x < world_dimensions.x);
  CHECK(randompos1.y > 0);
  CHECK(randompos1.y < world_dimensions.y);
  CHECK(randompos2.x > 0);
  CHECK(randompos2.x < world_dimensions.x);
  CHECK(randompos2.y > 0);
  CHECK(randompos2.y < world_dimensions.y);
  CHECK(randompos3.x > 0);
  CHECK(randompos3.x < world_dimensions.x);
  CHECK(randompos3.y > 0);
  CHECK(randompos3.y < world_dimensions.y);
  CHECK(randompos4.x > 0);
  CHECK(randompos4.x < world_dimensions.x);
  CHECK(randompos4.y > 0);
  CHECK(randompos4.y < world_dimensions.y);
  CHECK(randompos5.x > 0);
  CHECK(randompos5.x < world_dimensions.x);
  CHECK(randompos5.y > 0);
  CHECK(randompos5.y < world_dimensions.y);
}
