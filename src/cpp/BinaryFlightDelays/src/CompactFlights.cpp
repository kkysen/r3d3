#include <iostream>
#include <fstream>

#include "r3d3.h"
#include "Airline.h"
#include "Airport.h"
#include "RawFlight.h"
#include "Flights.h"
#include "util/Serializer.h"

const std::string DIR = "../../../data/flight-delays/";

std::ifstream airlinesFile(DIR + "airlines.csv");
std::ifstream airportsFile(DIR + "airports.csv");
std::ifstream flightsFile(DIR + "flights.csv");

using namespace r3d3;

void testBasic() {
    pf();
    p(readLines(DIR + "airlines.csv").size());
    
    std::vector<std::string> a;
    a.push_back("hello");
    a.push_back("h");
    
    p(narrowCast<int>(1));
}

void init() {
    pf();
    checkFile(airlinesFile);
    checkFile(airportsFile);
    checkFile(flightsFile);
    
    Airline::init(airlinesFile);
    Airport::init(airportsFile);
}

void testAirlinesAndAirports() {
    pf();
    auto airline = Airline(10);
    p(airline.name());
    p(airline.iataCode());
    
    auto airport = Airport(166);
    p(airport.iataCode());
    p(airport.name());
    p(airport.city());
    p(airport.state());
    p(airport.country());
    p(airport.location());
    
    p(DIR);
}

void analyzeFields() {
    pf();
    size_t numBits = 0;
    for (const auto field : RawFlight::analyzeFieldRanges(flightsFile)) {
        numBits += field.range.toNumBits();
        p(field);
    }
    p(numBits);
    const auto numBytes = static_cast<size_t>(numBits / 8.0);
    p(numBytes);
}

void compactFlights() {
    pf();
    
    const auto rawFlights = RawFlight::readFlights(flightsFile);
    const Flights flights(rawFlights);
    std::ofstream compactFlightsFile(DIR + "flights.bin");
    flights.serialize(*compactFlightsFile.rdbuf());
    std::cout << "Finished compacting flights.csv into flights.bin" << std::endl;
}

void testCompactFlights() {
    pf();
    
    std::ifstream compactFlightsFile(DIR + "flights.bin");
    const Flights flights(*compactFlightsFile.rdbuf());
    std::cout << "Finished loading flights.bin" << std::endl;
    
    const CompactFlight flight = flights[0][0];
    p(flight.departure().airport().iataCode());
    p(flight.departure().airport().name());
    p(flight.departure().airport().location());
    p(flight.arrival().airport().iataCode());
    p(flight.arrival().airport().name());
    p(flight.arrival().airport().location());
    p(flight.distance());
    p(flight.departure().airport().location() - flight.arrival().airport().location());
    
//    double distance = 0;
//    for (Flights::size_t i = 0; i < flights.size() / 300; i++) {
//        p(i << " " << distance);
//        p(flights[i].size() / 13);
//        for (FlightsInDay::size_t j = 0; j < flights[i].size() / 13; j++) {
//            p(j);
//            distance += flights[i][j].distance();
//        }
//    }
//    p(distance);
    
    p(std::fixed << flights.totalDistance() << std::scientific);
    
    const auto seattle = flight.arrival().airport();
    p(seattle.name());
    
    GeoLocation::setScaleContinentalUS(961.84375, 582.625);
    p(std::fixed);
    p(seattle.location());
    p(seattle.location().scale());
}

void testDate() {
    for (u16 day = 0; day <= 365; day++) {
        p(day << " " << Date(day));
    }
}

void testSerializer() {
    {
        std::ofstream compactFlightsFile(DIR + "flights.bin");
        std::streambuf* buf = compactFlightsFile.rdbuf();
        for (u16 i = 0; i < 100; i++) {
            Serializer<u16>::put(*buf, i);
        }
    }
    {
        std::ifstream compactFlightsFile(DIR + "flights.bin");
        std::streambuf* buf = compactFlightsFile.rdbuf();
        for (u16 i = 0; i < 100; i++) {
            p(Serializer<u16>::get(*buf));
        }
    }
}

void cpp() {
    //    testBasic();
    init();
//    testAirlinesAndAirports();
//    analyzeFields();
//    compactFlights();
    testCompactFlights();

//    testDate();
//    testSerializer();
}

void wasm() {
    pf();
}

int main() {
#ifndef __EMSCRIPTEN__
    cpp();
#else
    wasm();
#endif
    return 0;
}