// Bidimensional vector of double components and pertinent operations
#ifndef BS_V2D_HPP
#define BS_V2D_HPP

namespace bs {

struct V2D {
  double x{0};
  double y{0};

  V2D& operator+=(V2D const& r);
  V2D& operator-=(V2D const& r);
  V2D& operator*=(double m);
  V2D& operator/=(double d);
};
V2D operator+(V2D lhs, V2D const& rhs);
V2D operator-(V2D lhs, V2D const& rhs);
V2D operator*(double m, V2D lhs);
V2D operator*(V2D lhs, double m);
V2D operator/(V2D lhs, double d);

double dotprod(V2D const& a, V2D const& b);
double xprod(V2D const& a, V2D const& b);
double norm(V2D const& v);

}  // namespace bs

#endif