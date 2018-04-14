#include <iostream>
#include <fstream>

#include "r3d3.h"
#include "Airline.h"
#include "Airport.h"
#include "RawFlight.h"
#include "Flights.h"
#include "util/Serializer.h"

const std::string DIR = "../../data/flight-delays/";

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
}

void testCompactFlights() {
    pf();
    
    std::ifstream compactFlightsFile(DIR + "flights.bin");
    const Flights flights(*compactFlightsFile.rdbuf());
    std::cout << "Finished compacting flights.csv into flights.bin" << std::endl;
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

#ifndef __EMSCRIPTEN__

int main() {
//    testBasic();
    init();
//    testAirlinesAndAirports();
//    analyzeFields();
//    compactFlights();
    testCompactFlights();
    
//    testDate();
//    testSerializer();
    return 0;
}

#endif