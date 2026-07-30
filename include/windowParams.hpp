#ifndef BS_WINDOWPARAMS_HPP
#define BS_WINDOWPAAMS_HPP

#include <string>

namespace bs{
    struct WindowParams{
        std::string title{"Window"};

        unsigned int width{800};
        unsigned int height{600};

        unsigned int posX{400};
        unsigned int posY{300};

        unsigned int fps{60};

    };

}

#endif