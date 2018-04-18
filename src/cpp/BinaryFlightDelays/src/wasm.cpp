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
    
    #define MEMBER(class, name) PROPERTY(property, class, name)
    
    //
    
    #define METHOD(name) _METHOD(Flights, name)
    
    emscripten::class_<Flights>("Flights")
            STATIC_METHOD(Flights, jsCreate)
            METHOD(size)
            METHOD(numDays)
            METHOD(numFlights)
            METHOD(get)
            METHOD(flight)
            METHOD(totalDistance)
        //
            ;
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(FlightsInDay, name)
    
    emscripten::class_<FlightsInDay>("FlightsInDay")
            METHOD(size)
            METHOD(numFlights)
            METHOD(get)
        //
            ;
    
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
            METHOD(arrival)
        //
            ;
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Flight::Side, name)
    
    emscripten::class_<Flight::Side>("FlightSide")
            METHOD(time)
            METHOD(scheduledTime)
            METHOD(delay)
            METHOD(airport)
        //
            ;
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Airline, name)
    
    emscripten::class_<Airline>("Airline")
            STATIC_METHOD(Airline, count)
            STATIC_METHOD(Airline, numAirlines)
            STATIC_METHOD(Airline, of)
            METHOD(index)
            METHOD(iataCode)
            METHOD(name)
        //
            ;
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Airport, name)
    
    emscripten::class_<Airport>("Airport")
            STATIC_METHOD(Airport, count)
            STATIC_METHOD(Airport, numAirports)
            STATIC_METHOD(Airport, of)
            METHOD(index)
            METHOD(iataCode)
            METHOD(name)
            METHOD(city)
            METHOD(state)
            METHOD(country)
            METHOD(location)
            METHOD(distanceTo)
        //
            ;
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(GeoLocation, name)
    
    emscripten::class_<GeoLocation>("GeoLocation")
            STATIC_METHOD(GeoLocation, of)
            STATIC_METHOD(GeoLocation, setScaleContinentalUS)
            METHOD(longitude)
            METHOD(latitude)
            METHOD(distanceTo)
            METHOD(scale)
            METHOD(x)
            METHOD(y)
        //
            ;
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Date, name)
    
    emscripten::class_<Date>("Date")
            STATIC_METHOD(Date, of)
            METHOD(time)
            METHOD(year)
            METHOD(dayOfYear)
            METHOD(month)
            METHOD(dayOfMonth)
            METHOD(week)
            METHOD(dayOfWeek)
        //
            ;
    
    #undef METHOD
    
    //
    
    #define METHOD(name) _METHOD(Time, name)
    
    emscripten::class_<Time>("Time")
            STATIC_METHOD(Time, of)
            METHOD(minuteOfDay)
            METHOD(hourOfDay)
            METHOD(minuteOfHour)
            METHOD(isAM)
            METHOD(isPM)
            METHOD(add)
            METHOD(subtract)
            METHOD(negate)
        //
            ;
    
    #undef METHOD
    
    //
    
    #undef _METHOD
    
}

#endif