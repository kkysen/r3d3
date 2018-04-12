//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_FLIGHTS_H
#define BINARYFLIGHTDELAYS_FLIGHTS_H

#include <streambuf>
#include <future>

#include <emscripten/fetch.h>
#include <emscripten/bind.h>

#include "Flight.h"
#include "CompactFlight.h"
#include "Blob.h"

namespace r3d3 {
    
    class Flights final {
    
    private:
        
        static const size_t DAYS_IN_YEAR = 365; // for 2015
        
        using NumFlightsInDay = u16; // large enough for num flights on every day
        
        using FlightsInDay = std::vector<CompactFlight>;
        
        static NumFlightsInDay numFlightsInDay(FlightsInDay flightsInDay);
        
        using AllFlights = std::array<FlightsInDay, DAYS_IN_YEAR>;
        
        // TODO make this a pointer and use RAII
        
        const AllFlights flights;
        
        // TODO should Array flights be passed by reference, or will copying be elided?
        
        explicit Flights(AllFlights flights) noexcept;
        
        static AllFlights toAllFlights(std::streambuf& buf) noexcept;
    
    public:
        
        void serialize(std::streambuf& buf) const noexcept;
        
        explicit Flights(std::streambuf& buf) noexcept;
    
    private:
    
        static Flights create(Blob flightsData, Blob airportsData, Blob airlinesData);
        
    public:
        
        // called by JS in fetch calls with Uint8Arrays
        static Flights create(const u8* flightsData, size_t flightsDataLength,
                              const u8* airportsData, size_t airportsDataLength,
                              const u8* airlinesData, size_t airlinesDataLength);
        
        /*
         * For performance sake, instead of using JS to iterate over the flights,
         * filter them, and compute things based on them,
         * there will be an exported method here
         * that takes filter, callback, etc. functions/expressions.
         *
         * It will act like a mini-interpreter, like an SQL engine,
         * and will allow C++/wasm to compute things significantly faster
         * and much more memory efficiently.
         *
         * In some cases, this will just be calling a normal JS function from wasm,
         * but in cases where the inputs are restricted,
         * it's much easier to optimize/compile/interpret.
         *
         * Also, see devlog.txt: khyberS -- 2018-04-06 05:32:00
         */
        
        // TODO
        
    };
    
};

// Wasm exports

EMSCRIPTEN_BINDINGS(r3d3) { // NOLINT
    
    using namespace r3d3;
    
    using Flight = CompactFlight;
    
    #define PROPERTY(type, class, name) .type(#name, &class::name)
    
    #define _METHOD(class, name) PROPERTY(function, class, name)
    
    #define STATIC_METHOD(class, name) PROPERTY(class_property, class, name)
    
    //
    
    #define METHOD(name) _METHOD(Flight, name)
    
    emscripten::class_<Flight>("Flight")
            METHOD(date)
            METHOD(airline)
            METHOD(departure)
            METHOD(duration)
            METHOD(scheduledDuration)
            METHOD(distance)
            METHOD(arrival);
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Flight::Side, name)
    
    emscripten::class_<Flight::Side>("FlightSide")
            METHOD(time)
            METHOD(scheduledTime)
            METHOD(delay)
            METHOD(airport);
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Airline, name)
    
    emscripten::class_<Airline>("Airline")
            STATIC_METHOD(Airline, numAirlines)
            METHOD(iataCode)
            METHOD(name);
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Airport, name)
    
    emscripten::class_<Airport>("Airport")
            STATIC_METHOD(Airport, numAirports)
            METHOD(iataCode)
            METHOD(name)
            METHOD(city)
            METHOD(state)
            METHOD(country)
            METHOD(location)
            METHOD(distanceTo);
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(GeoLocation, name)
    
    emscripten::class_<GeoLocation>("GeoLocation")
            METHOD(latitude)
            METHOD(longitude)
            METHOD(distanceTo);
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Date, name)
    
    emscripten::class_<Date>("Date")
            METHOD(time)
            METHOD(year)
            METHOD(dayOfYear)
            METHOD(month)
            METHOD(dayOfMonth)
            METHOD(week)
            METHOD(dayOfWeek);
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Time, name)
    
    emscripten::class_<Time>("Time")
            METHOD(minuteOfDay)
            METHOD(hourOfDay)
            METHOD(minuteOfHour)
            METHOD(isAM)
            METHOD(isPM)
            METHOD(add)
            METHOD(subtract)
            METHOD(negate);
    
    #undef METHOD
    
    //
    
    #undef _METHOD
    
}


#endif //BINARYFLIGHTDELAYS_FLIGHTS_H
