#ifndef BS_RENDERPARAMS_HPP
#define BS_RENDERPARAMS_HPP

#include "windowParams.hpp"
namespace bs {
struct RenParams {

  WindowParams flock_window_parameters{};
  
  WindowParams statistics_window_parameters{};
  
  std::string font_path;

  bool op_rad{false};
};

/*
 // op_rad creates two circular shapes that represent the detection_radius (the
 radius wherein boids are seen by others) and the danger_radius (the radius
 whithin which there is a danger of collision with others)


                                 detect
                               ç-------ç
                            #             #
                         #                   #
                       /         danger        \
                      /         .-----.         \
                     |         /       \         |
                     |        |    Δ    |        |
                     |         \       /         |
                      \         '""""""         /
                       \                       /
                         #                   #
                           #               #
                             "--_______--"
*/

}  // namespace bs

#endif