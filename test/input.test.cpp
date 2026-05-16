
#include "input.hpp"

#include "doctest.h"
#include "simParams.hpp"

// Test di trim
TEST_CASE("trimming line with only spaces") {
    std::string line{"                                            "};
    std::string subline(flock::trimSpaces(line));
    std::string empty{};
    CHECK(empty == subline);
    CHECK(subline.empty());
}
