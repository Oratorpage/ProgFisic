#include "v2D.hpp"

#include <cmath>
namespace bs {

V2D& V2D::operator+=(V2D const& r) {
  x += r.x;
  y += r.y;
  return *this;
}

V2D& V2D::operator-=(V2D const& r) {
  x -= r.x;
  y -= r.y;
  return *this;
}

V2D& V2D::operator*=(double m) {
  x *= m;
  y *= m;
  return *this;
}

V2D& V2D::operator/=(double d) {
  x /= d;
  y /= d;
  return *this;
}

V2D operator+(V2D lhs, V2D const& rhs) { return lhs += rhs; }
V2D operator-(V2D lhs, V2D const& rhs) { return lhs -= rhs; }
V2D operator*(double m, V2D lhs) { return lhs *= m; }
V2D operator*(V2D lhs, double m) { return lhs *= m; }
V2D operator/(V2D lhs, double d) { return lhs /= d; }

double dotprod(V2D const& a, V2D const& b) { return a.x * b.x + a.y * b.y; }
double xprod(V2D const& a, V2D const& b) { return a.x * b.y - a.y * b.x; }
double norm(V2D const& v) { return std::sqrt(dotprod(v, v)); }

}  // namespace bs
