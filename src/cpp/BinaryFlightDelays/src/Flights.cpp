//
// Created by Khyber on 4/5/2018.
//

#include "Flights.h"

#include <cstring>
#include <iostream>

#include "util/Serializer.h"

namespace r3d3 {
    
    Flights::NumFlightsInDay Flights::numFlightsInDay(const Flights::FlightsInDay flightsInDay) {
        return static_cast<NumFlightsInDay>(flightsInDay.size());
    }
    
    Flights::Flights(const Flights::AllFlights flights) noexcept
            : flights(flights) {}
    
    Flights::AllFlights Flights::toAllFlights(std::streambuf& buf) noexcept {
        AllFlights flights;
        for (size_t i = 0; i < flights.size(); i++) {
            const NumFlightsInDay numFlightInDay = Serializer<NumFlightsInDay>::get(buf);
            FlightsInDay flightsInDay;
            flightsInDay.reserve(numFlightInDay);
            for (auto j = 0; j < numFlightInDay; j++) {
                flightsInDay.push_back(CompactFlight(buf));
            }
            flights[i] = flightsInDay;
        }
        return flights;
    }
    
    Flights::AllFlights Flights::toAllFlights(std::vector<RawFlight> rawFlights) noexcept {
        AllFlights flights;
        for (const auto& rawFlight : rawFlights) {
            const CompactFlight flight(rawFlight);
            flights[flight.date().dayOfYear()].push_back(flight);
        }
        return flights;
    }
    
    void Flights::serialize(std::streambuf& buf) const noexcept {
        for (const auto flightsInDay : flights) {
            Serializer<NumFlightsInDay>::put(buf, numFlightsInDay(flightsInDay));
            for (const auto flight : flightsInDay) {
                flight.serialize(buf);
            }
        }
    }
    
    Flights::Flights(std::streambuf& buf) noexcept
            : Flights(toAllFlights(buf)) {}
    
    Flights::Flights(const std::vector<RawFlight> rawFlights) noexcept
            : Flights(toAllFlights(rawFlights)) {}
    
    Flights Flights::create(const Blob flightsData, const Blob airportsData, const Blob airlinesData) {
        airlinesData.initUsingInputStream(Airline::init);
        airportsData.initUsingInputStream(Airport::init);
        std::stringbuf buf = flightsData.toStringBuf();
        return Flights(buf);
    }
    
    Flights Flights::createJS(
            const u8* flightsData, size_t flightsDataLength,
            const u8* airportsData, size_t airportsDataLength,
            const u8* airlinesData, size_t airlinesDataLength
    ) {
        return create(
                {.data = flightsData, .length = flightsDataLength},
                {.data = airportsData, .length = airportsDataLength},
                {.data = airlinesData, .length = airlinesDataLength}
        );
    }
    
};