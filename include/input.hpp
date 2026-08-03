#ifndef BS_INPUT_HPP
#define BS_INPUT_HPP

#include <string>

#include "config.hpp"

namespace bs {
std::string trimSpaces(std::string line);

int parseInt(std::string const& string_value);
unsigned 
unsiint parseUnsignedInt(std::string const& string_value);
double parseDouble(std::string const& string_value);
bool parseBool(std::string const& string_value);

Config readSimulationParams(std::string const& path);
}  // namespace bs

#endif