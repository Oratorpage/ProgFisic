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
  bs::Boid b12{{10., 10.}, {-40., 0.}, true};
  bs::Boid b13{{10., 10.}, {0., -40.}, true};
  bs::Boid b15{{10., 10.}, {-40., -40.}, true};
  bs::Boid b16{{10., 10.}, {40., -40.}, true};
  bs::Boid b17{{10., 10.}, {40., 40.}, true};
  bs::Boid b18{{10., 10.}, {-40., 40.}, true};

  // From here these should not be seen(360, with other may vary)
  bs::Boid b8{{-10., -10.}, {0., -97.}, true};
  bs::Boid b9{{-10., -10.}, {90.05, 0.}, true};
  bs::Boid b10{{10., 10.}, {91., 90.007}, true};
  bs::Boid b11{{-10., -10.}, {-102., 0.}, true};
  bs::Boid b14{{10., 10.}, {0., 90.0001}, true};
  bs::Boid b19{{10., 10.}, {-70., -70.}, true};
  bs::Boid b20{{10., 10.}, {70., -70.}, true};
  bs::Boid b21{{10., 10.}, {70., 70.}, true};
  bs::Boid b22{{10., 10.}, {-70., 70.}, true};
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
  CHECK(bs::isBoidVisibleInCone(b1, b12, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b13, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b15, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b16, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b17, bp1));
  CHECK(bs::isBoidVisibleInCone(b1, b18, bp1));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b14, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b19, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b20, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b21, bp1)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b22, bp1)));

  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp2{90., 30., 270., 250., 25., 0.7, 0.5, 0.3};
  // Angular vision (based on facing speed)(270 degrees)
  CHECK(!(bs::isBoidVisibleInCone(b1, b2, bp2)));
  CHECK(bs::isBoidVisibleInCone(b1, b3, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b4, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b5, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b6, bp2));
  CHECK(!(bs::isBoidVisibleInCone(b1, b7, bp2)));
  CHECK(bs::isBoidVisibleInCone(b1, b12, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b13, bp2));
  CHECK(!(bs::isBoidVisibleInCone(b1, b15, bp2)));
  CHECK(bs::isBoidVisibleInCone(b1, b16, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b17, bp2));
  CHECK(bs::isBoidVisibleInCone(b1, b18, bp2));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b14, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b19, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b20, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b21, bp2)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b22, bp2)));

  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp3{90., 30., 180., 250., 25., 0.7, 0.5, 0.3};
  // Angular vision (based on facing speed)(180 degrees)
  CHECK(!(bs::isBoidVisibleInCone(b1, b2, bp3)));
  CHECK(bs::isBoidVisibleInCone(b1, b3, bp3));
  CHECK(bs::isBoidVisibleInCone(b1, b4, bp3));
  CHECK(bs::isBoidVisibleInCone(b1, b5, bp3));
  CHECK(!(bs::isBoidVisibleInCone(b1, b6, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b7, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b12, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b13, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b15, bp3)));
  CHECK(bs::isBoidVisibleInCone(b1, b16, bp3));
  CHECK(bs::isBoidVisibleInCone(b1, b17, bp3));
  CHECK(bs::isBoidVisibleInCone(b1, b18, bp3));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b14, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b19, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b20, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b21, bp3)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b22, bp3)));

  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp4{90., 30., 90., 250., 25., 0.7, 0.5, 0.3};
  // Angular vision (based on facing speed)(90 degrees)
  CHECK(!(bs::isBoidVisibleInCone(b1, b2, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b3, bp4)));
  CHECK(bs::isBoidVisibleInCone(b1, b4, bp4));
  CHECK(bs::isBoidVisibleInCone(b1, b5, bp4));
  CHECK(!(bs::isBoidVisibleInCone(b1, b6, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b7, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b12, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b13, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b15, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b16, bp4)));
  CHECK(bs::isBoidVisibleInCone(b1, b17, bp4));
  CHECK(!(bs::isBoidVisibleInCone(b1, b18, bp4)));

  CHECK(!(bs::isBoidVisibleInCone(b1, b8, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b9, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b10, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b11, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b14, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b19, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b20, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b21, bp4)));
  CHECK(!(bs::isBoidVisibleInCone(b1, b22, bp4)));

  // Weird cases
  CHECK(bs::isBoidVisibleInCone(b1, bw1, bp1));
}
TEST_CASE("Collecting visible boids") {
  bs::Boid b1{{10., 10.}, {0., 0.}, true};
  // From here should be seen(360, with other may vary)
  bs::Boid b2{{-10., -10.}, {-3., -15.}, true};
  bs::Boid b3{{10., 10.}, {10., -8.}, true};
  bs::Boid b4{{-10., -10.}, {19., 0.}, true};
  bs::Boid b5{{10., 10.}, {0., 21.}, true};
  bs::Boid b6{{-10., -10.}, {-23., 2.}, true};
  bs::Boid b7{{10., 10.}, {-7., -14.}, true};
  bs::Boid b12{{10., 10.}, {-40., 0.}, true};
  bs::Boid b13{{10., 10.}, {0., -40.}, true};
  bs::Boid b15{{10., 10.}, {-40., -40.}, true};
  bs::Boid b16{{10., 10.}, {40., -40.}, true};
  bs::Boid b17{{10., 10.}, {40., 40.}, true};
  bs::Boid b18{{10., 10.}, {-40., 40.}, true};

  // From here these should not be seen(360, with other may vary)
  bs::Boid b8{{-10., -10.}, {0., -97.}, true};
  bs::Boid b9{{-10., -10.}, {90.05, 0.}, true};
  bs::Boid b10{{10., 10.}, {91., 90.007}, true};
  bs::Boid b11{{-10., -10.}, {-102., 0.}, true};
  bs::Boid b14{{10., 10.}, {0., 90.0001}, true};
  bs::Boid b19{{10., 10.}, {-70., -70.}, true};
  bs::Boid b20{{10., 10.}, {70., -70.}, true};
  bs::Boid b21{{10., 10.}, {70., 70.}, true};
  bs::Boid b22{{10., 10.}, {-70., 70.}, true};

  //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp1{90., 30., 360., 250., 25., 0.7, 0.5, 0.3};
  bs::BoidProperties bp2{90., 30., 270., 250., 25., 0.7, 0.5, 0.3};
  bs::BoidProperties bp3{90., 30., 180., 250., 25., 0.7, 0.5, 0.3};
  bs::BoidProperties bp4{90., 30., 90., 250., 25., 0.7, 0.5, 0.3};

  std::vector<bs::Boid> flock{b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,
                              b9,  b10, b11, b12, b13, b14, b15, b16,
                              b17, b18, b19, b20, b21, b22};
  // Here the index use is needed or else the memory address check done in
  // isBoidVisibleInCone fails due to the boid in the vector being a copy of b1,
  // cannot use b1 in place of flock[0]
  std::vector<bs::Boid const*> nearboid1{
      bs::collectVisibleBoids(flock, flock[0], bp1)};
  std::vector<bs::Boid const*> nearboid2{
      bs::collectVisibleBoids(flock, flock[0], bp2)};
  std::vector<bs::Boid const*> nearboid3{
      bs::collectVisibleBoids(flock, flock[0], bp3)};
  std::vector<bs::Boid const*> nearboid4{
      bs::collectVisibleBoids(flock, flock[0], bp4)};

  CHECK(nearboid1.size() == 12);
  CHECK(nearboid2.size() == 9);
  CHECK(nearboid3.size() == 6);
  CHECK(nearboid4.size() == 3);
}
TEST_CASE("Apply flock behavioural movement 360") {
  bs::Boid b1{{10., 10.}, {0., 0.}, false};
  // From here should be seen(360, with other may vary)
  bs::Boid b2{{-10., -10.}, {-3., -15.}, false};
  bs::Boid b3{{12., 10.}, {10., -8.}, false};
  bs::Boid b4{{-10., -13.}, {19., 0.}, false};
  bs::Boid b5{{14., 0.1}, {0., 21.}, false};
  bs::Boid b6{{-10., -15.}, {-23., 2.}, false};
  bs::Boid b7{{16., 20.}, {-7., -14.}, false};
  bs::Boid b12{{10., 17.}, {-40., 0.}, false};
  bs::Boid b13{{8., 30.}, {0., -40.}, false};
  bs::Boid b15{{102., 121.}, {-40., -40.}, false};
  bs::Boid b16{{10., 62.}, {40., -40.}, false};
  bs::Boid b17{{34., 23.}, {40., 40.}, false};
  bs::Boid b18{{11., 10.}, {-40., 40.}, false};

  // From here these should not be seen(360, with other may vary)
  bs::Boid b8{{-10., -10.}, {0., -97.}, false};
  bs::Boid b9{{-10., -10.}, {90.05, 0.}, false};
  bs::Boid b10{{10., 10.}, {91., 90.007}, false};
  bs::Boid b11{{-10., -10.}, {-102., 0.}, false};
  bs::Boid b14{{10., 10.}, {0., 90.0001}, false};
  bs::Boid b19{{10., 10.}, {-70., -70.}, false};
  bs::Boid b20{{10., 10.}, {70., -70.}, false};
  bs::Boid b21{{10., 10.}, {70., 70.}, false};
  bs::Boid b22{{10., 10.}, {-70., 70.}, false};
  double const dt{0.01};

  // //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp1{90., 30., 360., 250., 25., 0.7, 0.5, 0.3};

  std::vector<bs::Boid> flock{b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,
                              b9,  b10, b11, b12, b13, b14, b15, b16,
                              b17, b18, b19, b20, b21, b22};
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().x ==
        doctest::Approx(14.492).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().y ==
        doctest::Approx(24.079).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().x ==
        doctest::Approx(0.145).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().y ==
        doctest::Approx(0.241).epsilon(0.01));
}

TEST_CASE("Apply flock behavioural movement 270") {
  bs::Boid b1{{10., 10.}, {0., 0.}, false};
  // From here should be seen(360, with other may vary)
  bs::Boid b2{{-10., -10.}, {-3., -15.}, false};
  bs::Boid b3{{12., 10.}, {10., -8.}, false};
  bs::Boid b4{{-10., -13.}, {19., 0.}, false};
  bs::Boid b5{{14., 0.1}, {0., 21.}, false};
  bs::Boid b6{{-10., -15.}, {-23., 2.}, false};
  bs::Boid b7{{16., 20.}, {-7., -14.}, false};
  bs::Boid b12{{10., 17.}, {-40., 0.}, false};
  bs::Boid b13{{8., 30.}, {0., -40.}, false};
  bs::Boid b15{{102., 121.}, {-40., -40.}, false};
  bs::Boid b16{{10., 62.}, {40., -40.}, false};
  bs::Boid b17{{34., 23.}, {40., 40.}, false};
  bs::Boid b18{{11., 10.}, {-40., 40.}, false};

  // From here these should not be seen(360, with other may vary)
  bs::Boid b8{{-10., -10.}, {0., -97.}, false};
  bs::Boid b9{{-10., -10.}, {90.05, 0.}, false};
  bs::Boid b10{{10., 10.}, {91., 90.007}, false};
  bs::Boid b11{{-10., -10.}, {-102., 0.}, false};
  bs::Boid b14{{10., 10.}, {0., 90.0001}, false};
  bs::Boid b19{{10., 10.}, {-70., -70.}, false};
  bs::Boid b20{{10., 10.}, {70., -70.}, false};
  bs::Boid b21{{10., 10.}, {70., 70.}, false};
  bs::Boid b22{{10., 10.}, {-70., 70.}, false};
  double const dt{0.01};

  // //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp1{90., 30., 270., 250., 25., 0.7, 0.5, 0.3};
  std::vector<bs::Boid> flock{b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,
                              b9,  b10, b11, b12, b13, b14, b15, b16,
                              b17, b18, b19, b20, b21, b22};
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().x ==
        doctest::Approx(23.585).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().y ==
        doctest::Approx(8.291).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().x ==
        doctest::Approx(0.236).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().y ==
        doctest::Approx(0.083).epsilon(0.01));
}
TEST_CASE("Apply flock behavioural movement 180") {
  bs::Boid b1{{10., 10.}, {0., 0.}, false};
  // From here should be seen(360, with other may vary)
  bs::Boid b2{{-10., -10.}, {-3., -15.}, false};
  bs::Boid b3{{12., 10.}, {10., -8.}, false};
  bs::Boid b4{{-10., -13.}, {19., 0.}, false};
  bs::Boid b5{{14., 0.1}, {0., 21.}, false};
  bs::Boid b6{{-10., -15.}, {-23., 2.}, false};
  bs::Boid b7{{16., 20.}, {-7., -14.}, false};
  bs::Boid b12{{10., 17.}, {-40., 0.}, false};
  bs::Boid b13{{8., 30.}, {0., -40.}, false};
  bs::Boid b15{{102., 121.}, {-40., -40.}, false};
  bs::Boid b16{{10., 62.}, {40., -40.}, false};
  bs::Boid b17{{34., 23.}, {40., 40.}, false};
  bs::Boid b18{{11., 10.}, {-40., 40.}, false};

  // From here these should not be seen(360, with other may vary)
  bs::Boid b8{{-10., -10.}, {0., -97.}, false};
  bs::Boid b9{{-10., -10.}, {90.05, 0.}, false};
  bs::Boid b10{{10., 10.}, {91., 90.007}, false};
  bs::Boid b11{{-10., -10.}, {-102., 0.}, false};
  bs::Boid b14{{10., 10.}, {0., 90.0001}, false};
  bs::Boid b19{{10., 10.}, {-70., -70.}, false};
  bs::Boid b20{{10., 10.}, {70., -70.}, false};
  bs::Boid b21{{10., 10.}, {70., 70.}, false};
  bs::Boid b22{{10., 10.}, {-70., 70.}, false};
  double const dt{0.01};

  // //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp1{90., 30., 180., 250., 25., 0.7, 0.5, 0.3};
  std::vector<bs::Boid> flock{b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,
                              b9,  b10, b11, b12, b13, b14, b15, b16,
                              b17, b18, b19, b20, b21, b22};
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().x ==
        doctest::Approx(-17.249).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().y ==
        doctest::Approx(18.097).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().x ==
        doctest::Approx(-0.172).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().y ==
        doctest::Approx(0.181).epsilon(0.01));
}
TEST_CASE("Apply flock behavioural movement 90") {
  bs::Boid b1{{10., 10.}, {0., 0.}, false};
  // From here should be seen(360, with other may vary)
  bs::Boid b2{{-10., -10.}, {-3., -15.}, false};
  bs::Boid b3{{12., 10.}, {10., -8.}, false};
  bs::Boid b4{{-10., -13.}, {19., 0.}, false};
  bs::Boid b5{{14., 0.1}, {0., 21.}, false};
  bs::Boid b6{{-10., -15.}, {-23., 2.}, false};
  bs::Boid b7{{16., 20.}, {-7., -14.}, false};
  bs::Boid b12{{10., 17.}, {-40., 0.}, false};
  bs::Boid b13{{8., 30.}, {0., -40.}, false};
  bs::Boid b15{{102., 121.}, {-40., -40.}, false};
  bs::Boid b16{{10., 62.}, {40., -40.}, false};
  bs::Boid b17{{34., 23.}, {40., 40.}, false};
  bs::Boid b18{{11., 10.}, {-40., 40.}, false};

  // From here these should not be seen(360, with other may vary)
  bs::Boid b8{{-10., -10.}, {0., -97.}, false};
  bs::Boid b9{{-10., -10.}, {90.05, 0.}, false};
  bs::Boid b10{{10., 10.}, {91., 90.007}, false};
  bs::Boid b11{{-10., -10.}, {-102., 0.}, false};
  bs::Boid b14{{10., 10.}, {0., 90.0001}, false};
  bs::Boid b19{{10., 10.}, {-70., -70.}, false};
  bs::Boid b20{{10., 10.}, {70., -70.}, false};
  bs::Boid b21{{10., 10.}, {70., 70.}, false};
  bs::Boid b22{{10., 10.}, {-70., 70.}, false};
  double const dt{0.01};

  // //                   //detd,dand,angle,maxs,mins,sep,alig,cohe
  bs::BoidProperties bp1{90., 30., 90., 250., 25., 0.7, 0.5, 0.3};
  std::vector<bs::Boid> flock{b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,
                              b9,  b10, b11, b12, b13, b14, b15, b16,
                              b17, b18, b19, b20, b21, b22};
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().x ==
        doctest::Approx(22.474).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Vel().y ==
        doctest::Approx(-10.951).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().x ==
        doctest::Approx(0.225).epsilon(0.01));
  CHECK(bs::applyFlockBehaviouralMovement(flock, dt, bp1)[0].Pos().y ==
        doctest::Approx(-0.110).epsilon(0.01));
}