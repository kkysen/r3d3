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

namespace r3d3 {
    
    class Flights final {
    
    private:
        
        static const size_t DAYS_IN_YEAR = 365; // for 2015
        
        using NumFlightsInDay = u16; // large enough for num flights on every day
        
        using FlightsInDay = std::vector<Flight>;
        
        static NumFlightsInDay numFlightsInDay(FlightsInDay flightsInDay);
        
        using Array = std::array<FlightsInDay, DAYS_IN_YEAR>;
        
        // TODO make this a pointer and use RAII
        
        const Array flights;
        
        // TODO should Array flights be passed by reference, or will copying be elided?
        
        explicit Flights(Array flights) noexcept;
        
        static Array convert(std::streambuf& buf) noexcept;
        
        static bool startedLoading = false;
        static std::promise<const Flights&> promise;
        
        static const u32 MAX_FAILS = 10;
        static u32 numFails = 0;
        
        static void load(std::string url) noexcept;
    
    public:
        
        static const std::string FETCH_ROUTE = "/data/flights";
        
        void serialize(std::streambuf& buf) const noexcept;
        
        explicit Flights(std::streambuf& buf) noexcept;
        
        explicit Flights(const emscripten_fetch_t& fetch) noexcept;
        
        static std::future<const Flights&> get(std::string url = FETCH_ROUTE) noexcept;
        
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
