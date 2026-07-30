#ifndef BS_WORLDPARAMS_HPP
#define BS_WORLDPARAMS_HPP

#include "v2D.hpp"
namespace bs {
struct WorldParams {
  V2D dimensions{800, 600};
  bool toroidal{false};
};
}  // namespace bs

#endif