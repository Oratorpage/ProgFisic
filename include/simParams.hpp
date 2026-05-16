// Defines the parameters that will be used
#ifndef FLOCK_SIMPARAMS_HPP
#define FLOCK_SIMPARAMS_HPP

namespace flock {

struct SimParams {
  int non_pred_boidnum{0};
  int pred_boidnum{0};
  double separation{0.};
  double allignment{0.};
  double cohesion{0.};
  double detection_rad{0.};
  double danger_rad{0.};
  double angle_of_view{0.};
  bool toroidal{false};
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


 // angle_of_view changes the way boids see each other making it possible only
 through a certain angle, based on the type of creature the angle should vary,
 it is up to manual insertion


                \                   |                   /
                 \                  |   .^^^^^^.       /
                  \                 | ,'        ',    / detection distance
                   \                |'            '  /
                    \               |              '/
                     \              |              /
                      \             |             /
                       \            |            /
                        \           |           /
                         \          |          /
                          \         |,' ' ',  / danger distance
                           \        |       '/
                            \       |       /
                             \      |      /
                              \     |  α  /
                               \    |.''./
                                \   |   /
                                 \  |  /
                                  \ | /
                                   \|/
                                    Δ
                                   /|\
                                  / | \
                                 /  |  \
                                /   |   \
                               /    |    \
                              /     |     \
                             /      |      \
                            /       |       \
                           /        |        \

The danger distance is based on danger_rad when angle_of_view != 0. or !=365,
need to make the function and study this better
*/

}  // namespace flock

#endif