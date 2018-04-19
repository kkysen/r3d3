//
// Created by Khyber on 4/8/2018.
//

#include <vector>
#include "Airline.h"
#include "util/Blob.h"

namespace r3d3 {
    
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
    
    Airline::Airlines Airline::AIRLINES = {};
    
    Map<std::string, Airline::size_t> Airline::iataMap = Map<std::string, Airline::size_t>();
    
    void Airline::buildIataMap() noexcept {
        for (size_t i = 0; i < NUM_AIRLINES; i++) {
            iataMap[Airline(i).iataCode()] = i;
        }
    }
    
    bool Airline::initialized = false;
    
    void Airline::init(std::istream& stream) noexcept {
        if (initialized) {
            return;
        }
        initialized = true;
        AIRLINES = Airlines(stream, Fields::lineFilter, Fields::valueExtractor); // FIXME
        buildIataMap();
    }
    
    void Airline::load(std::string data) noexcept {
        Blob::load(data, init);
    }
    
    Airline::size_t Airline::count() noexcept {
        return NUM_AIRLINES;
    }
    
    Airline::size_t Airline::numAirlines() noexcept {
        return count();
    }
    
    Airline::Airline(const Airline::size_t index) noexcept : _index(index) {}
    
    Airline Airline::of(Airline::size_t index) noexcept {
        return Airline(index);
    }
    
    Airline::Airline(std::string iataCode) noexcept : Airline(iataMap[iataCode]) {}
    
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
        return fields().name;
    }
    
};