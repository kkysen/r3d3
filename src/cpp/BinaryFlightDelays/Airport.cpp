//
// Created by Khyber on 4/8/2018.
//

#include "Airport.h"

using namespace r3d3;

bool Airport::Fields::lineFilter(const Airport::size_t i) noexcept {
    return i > 0;
}

Airport::Fields Airport::Fields::valueExtractor(std::string line) noexcept {
    const std::vector<std::string> fields = split(line, ',');
    const double latitude = std::strtold(fields[4]); // FIXME
    const double longitude = std::strtold(fields[5]); // FIXME
    return {
            .iataCode = fields[0],
            .name = fields[1],
            .city = fields[2],
            .state = fields[3],
            .location = GeoLocation(latitude, longitude),
    };
}

const Airport::AIRPORTS = Airports(PATH, Fields::lineFilter, Fields::valueExtractor); // FIXME

void Airport::calculateDistances() noexcept {
    for (size_t i = 0; i < NUM_AIRPORTS; i++) {
        distances[i][i] = 0;
        for (size_t j = static_cast<size_t>(i + 1); j < NUM_AIRPORTS; j++) { // NOLINT
            const double distance = Airport(i).distanceTo(Airport(j));
            distances[i][j] = distances; // FIXME
            distances[j][i] = distances; // FIXME
        }
    }
}

void Airport::init(std::istream& stream) noexcept {
    initialized = true;
    AIRPORTS = Airports(stream, Fields::lineFilter, Fields::valueExtractor); // FIXME
    calculateDistances();
}

Airport::size_t Airport::numAirports() const noexcept {
    return NUM_AIRPORTS;
}

Airport::Airport(Airport::size_t index) noexcept : _index(index) {}

Airport::size_t Airport::index() const noexcept {
    return _index;
}

Airport::Fields Airport::fields() const noexcept {
    return AIRPORTS[_index];
}

std::string Airport::iataCode() const {
    return fields().iataCode;
}

std::string Airport::name() const noexcept {
    return fields().name;
}

std::string Airport::city() const noexcept {
    return fields().city;
}

std::string Airport::state() const noexcept {
    return fields().state;
}

std::string Airport::country() const noexcept {
    return fields().country;
}

GeoLocation Airport::location() const noexcept {
    return fields().location;
}

double Airport::distanceTo(const Airport airport) const noexcept {
    // optimize by precomputing distance
    return distances[_index][airport._index];
//    return location() - airport.location();
}