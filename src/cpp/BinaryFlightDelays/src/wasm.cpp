//
// Created by Khyber on 4/13/2018.
//

// Wasm exports

//#define __EMSCRIPTEN__ true

#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "Flights.h"

// TODO use nbind instead of embind
// TODO nbind has better C++ syntax, is more powerful, can compile to more targets, and generates .d.ts files

EMSCRIPTEN_BINDINGS(r3d3) { // NOLINT
    
    using namespace r3d3;
    
    using Flight = CompactFlight;
    
    #define PROPERTY(type, class, name) .type(#name, &class::name)
    
    #define _METHOD(class, name) PROPERTY(function, class, name)
    
    #define STATIC_METHOD(class, name) PROPERTY(class_function, class, name)
    
    //
    
    #define METHOD(name) _METHOD(Flights, name)
    
    emscripten::class_<Flights>("Flights")
            // TODO add other methods
            STATIC_METHOD(Flights, jsCreate);
    
    #undef METHOD
    
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

#endif