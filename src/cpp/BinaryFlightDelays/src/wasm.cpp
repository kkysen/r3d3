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
    #define MEMBER(class, name) PROPERTY(property, class, name)
    #define _METHOD(class, name) PROPERTY(function, class, name)
    #define _STATIC_METHOD(class, name) PROPERTY(class_function, class, name)
    
    //
    
    #define METHOD(name) _METHOD(Flights, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Flights, name)
    
    emscripten::class_<Flights>("Flights")
            STATIC_METHOD(create)
            METHOD(size)
            METHOD(numDays)
            METHOD(numFlights)
            METHOD(get)
            METHOD(flight)
            METHOD(totalDistance)
        //
            ;
    
    #undef METHOD
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(FlightsInDay, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(FlightsInDay, name)
    
    emscripten::class_<FlightsInDay>("FlightsInDay")
            METHOD(size)
            METHOD(numFlights)
            METHOD(get)
        //
            ;
    
    #undef METHOD
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(Flight, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Flight, name)
    
    emscripten::class_<Flight>("Flight")
            METHOD(date)
            METHOD(airline)
            METHOD(departure)
            METHOD(duration)
            METHOD(scheduledDuration)
            METHOD(distance)
            METHOD(arrival)
            STATIC_METHOD(projectedLocationPointer)
            STATIC_METHOD(projectedLocationSize)
            STATIC_METHOD(setProjectionPointer)
            METHOD(isRenderable)
            METHOD(interpolator)
        //
            ;
    
    #undef METHOD
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(Flight::Side, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Flight::Side, name)
    
    emscripten::class_<Flight::Side>("FlightSide")
            METHOD(time)
            METHOD(scheduledTime)
            METHOD(delay)
            METHOD(airport)
        //
            ;
    
    #undef METHOD
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(Flight::Interpolator, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Flight::Interpolator, name)
    
    emscripten::class_<Flight::Interpolator>("FlightInterpolator")
            STATIC_METHOD(statePointer)
            STATIC_METHOD(stateSize)
            METHOD(duration)
            METHOD(interpolate)
            METHOD(update)
        //
            ;
    
    #undef METHOD
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(Airline, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Airline, name)
    
    emscripten::class_<Airline>("Airline")
            STATIC_METHOD(load)
            STATIC_METHOD(count)
            STATIC_METHOD(numAirlines)
            STATIC_METHOD(of)
            METHOD(index)
            METHOD(iataCode)
            METHOD(name)
        //
            ;
    
    #undef METHOD
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(Airport, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Airport, name)
    
    emscripten::class_<Airport>("Airport")
            STATIC_METHOD(load)
            STATIC_METHOD(count)
            STATIC_METHOD(numAirports)
            STATIC_METHOD(of)
            STATIC_METHOD(ofIataCode)
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
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(GeoLocation, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(GeoLocation, name)
    
    emscripten::class_<GeoLocation>("GeoLocation")
            STATIC_METHOD(of)
            METHOD(longitude)
            METHOD(latitude)
            METHOD(distanceTo)
            // don't work correctly
//            METHOD(scale)
//            METHOD(x)
//            METHOD(y)
        //
            ;
    
    #undef METHOD
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(Date, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Date, name)
    
    emscripten::class_<Date>("Date")
            STATIC_METHOD(of)
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
    #undef STATIC_METHOD
    
    //
    
    #define METHOD(name) _METHOD(Time, name)
    #define STATIC_METHOD(name) _STATIC_METHOD(Time, name)
    
    emscripten::class_<Time>("Time")
            STATIC_METHOD(of)
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
    #undef STATIC_METHOD
    
    //
    
    #undef _STATIC_METHOD
    #undef _METHOD
    #undef MEMBER
    #undef PROPERTY
    
}

#endif