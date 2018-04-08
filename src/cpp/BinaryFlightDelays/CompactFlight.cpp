//
// Created by Khyber on 4/5/2018.
//

#include <cstdlib>
#include <limits>
#include <sstream>

#include "CompactFlight.h"
#include "Serializer.h"

using namespace r3d3;



// CompactFlight::Side constructors and deserialization

CompactFlight::Side::Side(const Bits bits) noexcept : bits(bits) {}

CompactFlight::Side::Bits CompactFlight::Side::convert(const RawFlight::Side& side) noexcept(false) {
    return {
            .time = narrowCast<u16, TIME_BITS>(side.minute),
            .delay = narrowCast<u16, DELAY_BITS>(side.delay - DELAY_OFFSET),
            .airport = narrowCast<Airport, AIRPORT_BITS>(side.airport),
    };
}

CompactFlight::Side::Side(const RawFlight::Side& side) noexcept(false) : Side(convert(side)) {}



// CompactFlight constructors, deserialization, and serialization

CompactFlight::CompactFlight(const Bits bits) noexcept : bits(bits) {}

CompactFlight::Bits CompactFlight::convert(const RawFlight& flight) noexcept(false) {
    return {
            .day = narrowCast<u16, DAY_BITS>(flight.dayOfYear),
            .airline = narrowCast<Airline, AIRLINE_BITS>(flight.airline),
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
    return bits.airport;
}



// CompactFlight bit accessors

u16 CompactFlight::dayOfYear() const noexcept {
    return bits.day;
}

Airline CompactFlight::airline() const noexcept {
    return bits.airline;
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

Time CompactFlight::Side::delay() const {
    return Time(delayMinutes());
}

Time CompactFlight::Side::scheduledTime() const {
    return time() - delay();
}

std::string CompactFlight::Side::airportName() const noexcept {
    return AIRPORTS[airport()];
}



// CompactFlight methods

Date CompactFlight::date() const noexcept {
    return Date(dayOfYear());
}

Time CompactFlight::duration() const noexcept {
    return arrival().time() - departure().time();
}

Time CompactFlight::scheduledDuration() const noexcept {
    // TODO hopefully this will all be inlined, so it'll only be a bunch of arithmetic operations
    return arrival().scheduledTime() - departure().scheduledTime();
}

std::string CompactFlight::airlineName() const noexcept {
    return AIRLINES[airline()];
}
