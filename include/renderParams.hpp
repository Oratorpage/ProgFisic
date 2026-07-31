#ifndef BS_RENDERPARAMS_HPP
#define BS_RENDERPARAMS_HPP

#include "windowParams.hpp"
namespace bs {
struct RenParams {
  // Render

  WindowParams flock_window_parameters{};
  
  WindowParams statistics_window_parameters{};

  bool op_rad{false};
};
}  // namespace bs

#endif