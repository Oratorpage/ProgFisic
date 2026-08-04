#ifndef BS_INPUT_HPP
#define BS_INPUT_HPP

#include <string>

#include "config.hpp"

namespace bs {
std::string trimSpaces(std::string const& line);

int parseInt(std::string const& string_value);
unsigned int parseUnsignedInt(std::string const& string_value);
double parseDouble(std::string const& string_value);
bool parseBool(std::string const& string_value);

void readSimulationSection(SimParams& sim_par,
                           std::unordered_set<std::string>& initialized_keys,
                           std::string const& key,
                           std::string const& string_value,
                           std::size_t line_number);
void readRenderSection(RenParams& ren_par,
                       std::unordered_set<std::string>& initialized_keys,
                       std::string const& key, std::string const& string_value,
                       std::size_t line_number);
void readWorldSection(WorldParams& wrld_par,
                      std::unordered_set<std::string>& initialized_keys,
                      std::string const& key, std::string const& string_value,
                      std::size_t line_number);
void readBoidsSection(BoidProperties& boid_par,
                      std::unordered_set<std::string>& initialized_keys,
                      std::string const& key, std::string const& string_value,
                      std::size_t line_number);

void extractKeyValue(std::string const& line, std::string& key,
                     std::string& string_value);

Config readParams(std::string const& path);

void checkSimulationKeys(
    std::unordered_set<std::string> const& initialized_keys);
void checkRenderKeys(std::unordered_set<std::string> const& initialized_keys);
void checkWorldKeys(std::unordered_set<std::string> const& initialized_keys);
void checkBoidsKeys(std::unordered_set<std::string> const& initialized_keys);

}  // namespace bs

#endif