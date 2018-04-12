//
// Created by Khyber on 4/8/2018.
//

#include <vector>
#include "Airline.h"

using namespace r3d3;

bool Airline::Fields::lineFilter(const Airline::size_t i) noexcept {
    return i > 0;
}

Airline::Fields Airline::Fields::valueExtractor(const std::string line) noexcept {
    const std::vector<std::string> fields = split(line, ',');
    return {
            .iataCode = fields[0],
            .name = fields[1],
    };
}

void Airline::init(std::istream& stream) noexcept {
    initialized = true;
    AIRLINES = Airlines(stream, Fields::lineFilter, Fields::valueExtractor); // FIXME
}

Airline::size_t Airline::numAirlines() const noexcept {
    return NUM_AIRLINES;
}

Airline::Airline(const Airline::size_t index) noexcept : _index(index) {}

Airline::size_t Airline::index() const noexcept {
    return _index;
}

Airline::Fields Airline::fields() const noexcept {
    return AIRLINES[_index];
}

std::string Airline::iataCode() const noexcept {
    return fields().iataCode;
}

std::string Airline::name() const noexcept {
    return fields().iataCode;
}
