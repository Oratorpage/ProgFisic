#include "v2D.hpp"

#include "doctest.h"

TEST_CASE("operator+=") {
  bs::V2D v{1., 1.};
  bs::V2D b{-1., -1.};
  bs::V2D p{1., -1.};

  v += b;
  b += p;

  CHECK(v.x == 0.);
  CHECK(v.y == 0.);
  CHECK(b.x == 0.);
  CHECK(b.y == -2.);
}
TEST_CASE("operator-=") {
  bs::V2D v{1., 1.};
  bs::V2D b{-1., -1.};
  bs::V2D p{1., -1.};

  v -= b;
  b -= p;

  CHECK(v.x == 2.);
  CHECK(v.y == 2.);
  CHECK(b.x == -2.);
  CHECK(b.y == -0.);
}
TEST_CASE("operator*=") {
  bs::V2D v{1., 1.};
  bs::V2D b{-1., -1.};
  bs::V2D p{1., -1.};
  double m{2.};
  double n{-3.};
  double g{1.5};

  v *= m;
  b *= n;
  p *= g;

  CHECK(v.x == 2.);
  CHECK(v.y == 2.);
  CHECK(b.x == 3.);
  CHECK(b.y == 3.);
  CHECK(p.x == 1.5);
  CHECK(p.y == -1.5);
}
TEST_CASE("operator/=") {
  bs::V2D v{1., 1.};
  bs::V2D b{-1., -1.};
  bs::V2D p{1., -1.};
  double m{2.};
  double n{-3.};
  double g{1.5};

  v /= m;
  b /= n;
  p /= g;

  CHECK(v.x == 0.5);
  CHECK(v.y == 0.5);
  CHECK(b.x == doctest::Approx(0.333).epsilon(0.001));
  CHECK(b.y == doctest::Approx(0.333).epsilon(0.001));
  CHECK(p.x == doctest::Approx(0.667).epsilon(0.001));
  CHECK(p.y == doctest::Approx(-0.667).epsilon(0.001));
}
TEST_CASE("operator+") {
  bs::V2D v{1., 1.};
  bs::V2D b{-1., -1.};
  bs::V2D p{v + b};

  CHECK(p.x == 0.);
  CHECK(p.y == 0.);
}
TEST_CASE("operator-") {
  bs::V2D v{1., 1.};
  bs::V2D b{-1., -1.};
  bs::V2D p{v - b};

  CHECK(p.x == 2.);
  CHECK(p.y == 2.);
}
TEST_CASE("operator*") {
  bs::V2D v{1., 1.};
  double d{2.};
  bs::V2D b{v * d};

  CHECK(b.x == 2.);
  CHECK(b.y == 2.);
}
TEST_CASE("operator/") {
  bs::V2D v{1., 1.};
  double d{2.};
  bs::V2D b{v / d};

  CHECK(b.x == 0.5);
  CHECK(b.y == 0.5);
}
TEST_CASE("dotprod") {
  bs::V2D v{1., -5.};
  bs::V2D b{-2., -3.};
  bs::V2D p{-8., 2.};
  double res1{bs::dotprod(v, b)};
  double res2{bs::dotprod(v, p)};
  double res3{bs::dotprod(b, p)};
  double res4{bs::dotprod(b, v)};

  CHECK(res1 == 13.);
  CHECK(res2 == -18.);
  CHECK(res3 == 10.);
  CHECK(res4 == 13.);
}
TEST_CASE("xprod") {
  bs::V2D v{1., -5.};
  bs::V2D b{-2., -3.};
  bs::V2D p{-8., 2.};
  double res1{bs::xprod(v, b)};
  double res2{bs::xprod(v, p)};
  double res3{bs::xprod(b, p)};
  double res4{bs::xprod(b, v)};

  CHECK(res1 == -13.);
  CHECK(res2 == -38.);
  CHECK(res3 == -28.);
  CHECK(res4 == 13.);
}
TEST_CASE("norm"){
    bs::V2D v{1., -5.};
  bs::V2D b{-2., -3.};
  bs::V2D p{-8., 2.};
  double res1{norm(v)};
  double res2{norm(b)};
  double res3{norm(p)};

  CHECK(res1 == doctest::Approx(5.099).epsilon(0.001));
  CHECK(res2 == doctest::Approx(3.606).epsilon(0.001));
  CHECK(res3 == doctest::Approx(8.246).epsilon(0.001));
}