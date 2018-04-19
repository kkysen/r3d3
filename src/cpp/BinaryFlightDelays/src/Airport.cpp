//
// Created by Khyber on 4/8/2018.
//

#include <iostream>
#include "Airport.h"
#include "util/Blob.h"

namespace r3d3 {
    
    bool Airport::Fields::lineFilter(const Airport::size_t i) noexcept {
        return i > 0;
    }
    
    Airport::Fields Airport::Fields::valueExtractor(std::string line) noexcept {
        const std::vector<std::string> fields = split(line, ',');
        const double latitude = std::strtod(fields[5].c_str(), nullptr);
        const double longitude = std::strtod(fields[6].c_str(), nullptr);
        return {
                .iataCode = fields[0],
                .name = fields[1],
                .city = fields[2],
                .state = fields[3],
                .country = fields[4],
                .location = GeoLocation(longitude, latitude),
        };
    }
    
    Airport::Airports Airport::AIRPORTS = {};
    
    Map<std::string, Airport::size_t> Airport::iataMap = Map<std::string, Airport::size_t>();
    
    void Airport::buildIataMap() noexcept {
        for (size_t i = 0; i < NUM_AIRPORTS; i++) {
            iataMap[Airport(i).iataCode()] = i;
        }
    }
    
    double Airport::distances[Airport::NUM_AIRPORTS][Airport::NUM_AIRPORTS] = {};
    
    void Airport::calculateDistances() noexcept {
        for (size_t i = 0; i < NUM_AIRPORTS; i++) {
            distances[i][i] = 0;
            for (size_t j = static_cast<size_t>(i + 1); j < NUM_AIRPORTS; j++) { // NOLINT
                const double distance = Airport(i).location() - Airport(j).location();
                distances[i][j] = distance;
                distances[j][i] = distance;
            }
        }
    }
    
    bool Airport::initialized = false;
    
    void Airport::init(std::istream& stream) noexcept {
        if (initialized) {
            return;
        }
        initialized = true;
        AIRPORTS = Airports(stream, Fields::lineFilter, Fields::valueExtractor); // FIXME
        calculateDistances();
        buildIataMap();
    }
    
    void Airport::load(std::string data) noexcept {
        Blob::load(data, init);
    }
    
    Airport::size_t Airport::count() noexcept {
        return NUM_AIRPORTS;
    }
    
    Airport::size_t Airport::numAirports() noexcept {
        return count();
    }
    
    Airport::Airport(Airport::size_t index) noexcept : _index(index) {}
    
    Airport Airport::of(Airport::size_t index) noexcept {
        return Airport(index);
    }
    
    Airport::Airport(std::string iataCode) noexcept : Airport(iataMap[iataCode]) {}

    Airport Airport::ofIataCode(std::string iataCode) noexcept {
        return Airport(iataCode);
    }
    
    Airport::size_t Airport::index() const noexcept {
        return _index;
    }
    
    Airport::Fields Airport::fields() const noexcept {
        return AIRPORTS[_index];
    }
    
    std::string Airport::iataCode() const noexcept {
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
//        return location() - airport.location();
    }
    
};