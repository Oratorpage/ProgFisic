#ifndef BS_WORLDPARAMS_HPP
#define BS_WORLDPARAMS_HPP

namespace bs {
struct WorldParams {
  // Qui si potrebbe fare con un V2D in maniera da raggrupparlo
  double width{800};
  double height{600};
  bool toroidal{false};
};
}  // namespace bs

#endif