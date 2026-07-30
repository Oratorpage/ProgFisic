#ifndef BS_BOIDPROPERTIES_HPP
#define BS_BOIDPROPERTIES_HPP

namespace bs {
struct BoidProperties {
    double detection_radius{};
    double danger_radius{};
    double angle_of_view{};
    double maxspeed{};
};
}  // namespace bs

#endif