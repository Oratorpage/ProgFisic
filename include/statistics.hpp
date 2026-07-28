#ifndef BS_STATISTICS_HPP
#define BS_STATISTICS_HPP

#include "v2D.hpp"
#include "string"

namespace bs{
    struct Statistics{
        V2D cm_pos{0,0};
        V2D avg_vel{0,0};
        int in_window_count{0};
        std::string output{"invalid"};
    };
}

#endif