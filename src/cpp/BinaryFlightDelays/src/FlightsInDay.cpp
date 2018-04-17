//
// Created by Khyber on 4/15/2018.
//

#include "FlightsInDay.h"
#include "util/Serializer.h"

namespace r3d3 {
    
    FlightsInDay::FlightsInDay() noexcept = default;
    
    FlightsInDay::FlightsInDay(const std::vector<CompactFlight> flights) noexcept : flights(flights) {}
    
    std::vector<CompactFlight> FlightsInDay::deserialize(std::streambuf& buf) noexcept {
        const size_t numFlights = Serializer<size_t>::get(buf);
        std::vector<CompactFlight> flights;
        flights.reserve(numFlights);
        for (size_t i = 0; i < numFlights; i++) {
            flights.push_back(CompactFlight(buf));
        }
        return flights;
    }
    
    FlightsInDay::FlightsInDay(std::streambuf& buf) noexcept : FlightsInDay(deserialize(buf)) {}
    
    void FlightsInDay::serialize(std::streambuf& buf) const noexcept {
        Serializer<size_t>::put(buf, numFlights());
        for (const auto flight : flights) {
            flight.serialize(buf);
        }
    }
    
    FlightsInDay::size_t FlightsInDay::size() const noexcept {
        return static_cast<size_t>(flights.size());
    }
    
    FlightsInDay::size_t FlightsInDay::numFlights() const noexcept {
        return size();
    }
    
    CompactFlight FlightsInDay::operator[](size_t i) const noexcept {
        return flights[i];
    }
    
    CompactFlight FlightsInDay::get(size_t i) const noexcept {
        return (*this)[i];
    }
    
};