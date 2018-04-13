//
// Created by Khyber on 4/5/2018.
//

#include <cstdlib>
#include <limits>
#include <sstream>

#include "CompactFlight.h"
#include "util/Serializer.h"

namespace r3d3 {
    
    

    // CompactFlight::Side constructors and deserialization
    
    CompactFlight::Side::Side(const Bits bits) noexcept : bits(bits) {}
    
    CompactFlight::Side::Bits CompactFlight::Side::convert(const RawFlight::Side& side) noexcept(false) {
        return {
                .time = narrowCast<u16, TIME_BITS>(side.minute),
                .delay = narrowCast<u16, DELAY_BITS>(side.delay - DELAY_OFFSET),
                .airport = narrowCast<Airport::size_type, AIRPORT_BITS>(side.airport.index()),
        };
    }
    
    CompactFlight::Side::Side(const RawFlight::Side& side) noexcept(false) : Side(convert(side)) {}



    // CompactFlight constructors, deserialization, and serialization
    
    CompactFlight::CompactFlight(const Bits bits) noexcept : bits(bits) {}
    
    CompactFlight::Bits CompactFlight::convert(const RawFlight& flight) noexcept(false) {
        return {
                .day = narrowCast<u16, DAY_BITS>(flight.dayOfYear),
                .airline = narrowCast<Airline::size_type, AIRLINE_BITS>(flight.airline.index()),
                .departure = Departure(flight.departure),
                .arrival = Arrival(flight.arrival),
        };
    }
    
    CompactFlight::CompactFlight(const RawFlight& flight) noexcept(false) : CompactFlight(convert(flight)) {}
    
    CompactFlight::Bits CompactFlight::convert(std::streambuf& buf) noexcept {
        return Serializer<Bits>::get(buf);
    }
    
    CompactFlight::CompactFlight(std::streambuf& buf) noexcept : CompactFlight(convert(buf)) {}
    
    void CompactFlight::serialize(std::streambuf& buf) const noexcept {
        Serializer<Bits>::put(buf, bits);
    }



    // CompactFlight::Side bit accessors
    
    i16 CompactFlight::Side::minuteOfDay() const noexcept {
        return bits.time;
    }
    
    i16 CompactFlight::Side::delayMinutes() const noexcept {
        return bits.delay + DELAY_OFFSET;
    }
    
    Airport CompactFlight::Side::airport() const noexcept {
        return Airport(bits.airport);
    }



    // CompactFlight bit accessors
    
    u16 CompactFlight::dayOfYear() const noexcept {
        return bits.day;
    }
    
    Airline CompactFlight::airline() const noexcept {
        return Airline(bits.airline);
    }
    
    CompactFlight::Departure CompactFlight::departure() const noexcept {
        return Departure(bits.departure);
    }
    
    CompactFlight::Arrival CompactFlight::arrival() const noexcept {
        return Arrival(bits.arrival);
    }



    // CompactFlight::Side methods
    
    Time CompactFlight::Side::time() const noexcept {
        return Time(minuteOfDay());
    }
    
    Time CompactFlight::Side::delay() const noexcept {
        return Time(delayMinutes());
    }
    
    Time CompactFlight::Side::scheduledTime() const noexcept {
        return time() - delay();
    }



    // CompactFlight methods
    
    Date CompactFlight::date() const noexcept {
        return Date(dayOfYear());
    }
    
    Time CompactFlight::duration() const noexcept {
        return Time::between(departure().time(), arrival().time());
    }
    
    Time CompactFlight::scheduledDuration() const noexcept {
        return Time::between(departure().scheduledTime(), arrival().scheduledTime());
    }
    
    double CompactFlight::distance() const noexcept {
        // method call distanceTo() allows Airport to possibly cache distances in whatever way
        return departure().airport().distanceTo(arrival().airport());
    }
    
};