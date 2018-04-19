//
// Created by Khyber on 4/5/2018.
//

#include "Flights.h"

#include <cstring>
#include <iostream>

namespace r3d3 {
    
    std::size_t Flights::countNumFlights(const AllFlights flights) noexcept {
        std::size_t numFlights = 0;
        for (const auto flightsInDay : flights) {
            numFlights += flightsInDay.size();
        }
        return numFlights;
    }
    
    Flights::Flights(const Flights::AllFlights flights) noexcept
            : flights(flights), _numFlights(countNumFlights(flights)) {}
    
    Flights::AllFlights Flights::deserialize(std::streambuf& buf) noexcept {
        AllFlights flights;
        for (size_t i = 0; i < flights.size(); i++) {
            flights[i] = FlightsInDay(buf);
        }
        return flights;
    }
    
    Flights::AllFlights Flights::toAllFlights(std::vector<RawFlight> rawFlights) noexcept {
        std::array<std::vector<CompactFlight>, DAYS_IN_YEAR> flights;
        for (const auto& rawFlight : rawFlights) {
            const CompactFlight flight(rawFlight);
            flights[flight.date().dayOfYear()].push_back(flight);
        }
        AllFlights allFlights;
        for (size_t i = 0; i < allFlights.size(); i++) {
            allFlights[i] = FlightsInDay(flights[i]);
        }
        return allFlights;
    }
    
    void Flights::serialize(std::streambuf& buf) const noexcept {
        for (const auto flightsInDay : flights) {
            flightsInDay.serialize(buf);
        }
    }
    
    Flights::Flights(std::streambuf& buf) noexcept
            : Flights(deserialize(buf)) {}
    
    Flights::Flights(const std::vector<RawFlight> rawFlights) noexcept
            : Flights(toAllFlights(rawFlights)) {}
    
    Flights Flights::create(std::string flightsData) noexcept {
        std::stringbuf buf = Blob::ofString(flightsData).toStringBuf();
        return Flights(buf);
    }
    
    Flights::size_t Flights::size() const noexcept {
        return flights.size();
    }
    
    Flights::size_t Flights::numDays() const noexcept {
        return size();
    }
    
    std::size_t Flights::numFlights() const noexcept {
        return _numFlights;
    }
    
    FlightsInDay Flights::operator[](Flights::size_t day) const noexcept {
        return flights[day];
    }
    
    FlightsInDay Flights::get(Flights::size_t day) const noexcept {
        return (*this)[day];
    }
    
    CompactFlight Flights::flight(Flights::size_t day, Flights::size_t i) const noexcept {
        return get(day).get(i);
    }
    
    double Flights::totalDistance() const noexcept {
        double distance = 0;
        for (Flights::size_t i = 0; i < flights.size(); i++) {
//            p(i);
            for (FlightsInDay::size_t j = 0; j < flights[i].size(); j++) {
                distance += flights[i][j].distance();
            }
        }
        return distance;
    }
    
};