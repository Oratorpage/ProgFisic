#include "behaviour.hpp"

#include "doctest.h"

TEST_CASE("distanceSquared") {
  bs::V2D a{3., 5.};
  bs::V2D b{7., -9.};
  CHECK(bs::distSq(a, b) == doctest::Approx(212).epsilon(0.01));
}
TEST_CASE("isBoidVisibleInCone?") {
  // The one who sees
  bs::Boid b1{{10., 10.}, {0., 0.}, true};
  // From here should be seen(360, with other may vary)
  bs::Boid b2{{-10., -10.}, {-3., -15.}, true};
  bs::Boid b3{{10., 10.}, {10., -8.}, true};
  bs::Boid b4{{-10., -10.}, {19., 0.}, true};
  bs::Boid b5{{10., 10.}, {0., 21.}, true};
  bs::Boid b6{{-10., -10.}, {-23., 2.}, true};
  bs::Boid b7{{10., 10.}, {-7., -14.}, true};
  // From here these should not be seen(360, with other may vary)
  bs::Boid b8{{-10., -10.}, {0., -97.}, true};
  bs::Boid b9{{-10., -10.}, {90.05, 0.}, true};
  bs::Boid b10{{10., 10.}, {91., 90.007}, true};
  bs::Boid b11{{-10., -10.}, {-102., 0.}, true};
  // Weird cases
  bs::Boid bw1{{-10., -10.}, {-0.001, 0.002}, true};
  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp1{90., 30., 360., 250., 25., 0.7, 0.5, 0.3};

  // Shouldn't see the same one
  CHECK(!(bs::isBoidVisibleInCone(b1, b1, bp1)));

  // Circular complete vision (360 degrees)
  CHECK(bs::isBoidVisibleInCone(b1, b2, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b3, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b4, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b5, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b6, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b7, bp1));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp1)));

  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp2{90., 30., 270., 250., 25., 0.7, 0.5, 0.3};
  // Angular vision (based on facing speed)(270 degrees)
  CHECK(!(bs::isBoidVisibleInCone(b1, b2, bp2)));
  CHECK(bs::isBoidVisibleInCone(b1, b3, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b4, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b5, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b6, bp2));
  CHECK(!(bs::isBoidVisibleInCone(b1, b7, bp2)));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp2)));

  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp3{90., 30., 180., 250., 25., 0.7, 0.5, 0.3};
  // Angular vision (based on facing speed)(180 degrees)
  CHECK(!(bs::isBoidVisibleInCone(b1, b2, bp3)));
  CHECK(bs::isBoidVisibleInCone(b1, b3, bp3));
  CHECK(bs::isBoidVisibleInCone(b1, b4, bp3));
  CHECK(bs::isBoidVisibleInCone(b1, b5, bp3));
  CHECK(!(bs::isBoidVisibleInCone(b1, b6, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b7, bp3)));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp3)));

  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp4{90., 30., 90., 250., 25., 0.7, 0.5, 0.3};
  // Angular vision (based on facing speed)(90 degrees)
  CHECK(!(bs::isBoidVisibleInCone(b1, b2, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b3, bp4)));
  CHECK(bs::isBoidVisibleInCone(b1, b4, bp4));  //
  CHECK(bs::isBoidVisibleInCone(b1, b5, bp4));  //
  CHECK(!(bs::isBoidVisibleInCone(b1, b6, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b7, bp4)));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp4)));

  // Weird cases
  CHECK(bs::isBoidVisibleInCone(b1, bw1, bp1));

  
}