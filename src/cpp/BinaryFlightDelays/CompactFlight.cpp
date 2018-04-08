//
// Created by Khyber on 4/5/2018.
//

#include <cstdlib>
#include <limits>
#include <sstream>

#include "CompactFlight.h"

using namespace r3d3;

template <size_t offset>
CompactFlight::Side<offset>::Side(const Bits bits) noexcept : bits(bits) {}

template <size_t offset>
std::string CompactFlight::Side<offset>::airportName() const noexcept {
    return AIRPORTS[airport()];
}

std::string CompactFlight::airlineName() const noexcept {
    return AIRLINES[airline()];
}

CompactFlight::Departure CompactFlight::departure() const noexcept {
    return Departure(bits);
}

CompactFlight::Arrival CompactFlight::arrival() const noexcept {
    return Arrival(bits);
}

template <typename T>
constexpr size_t numBits() {
    return (size_t) std::numeric_limits<T>::digits;
}

constexpr u64 allOnes(const u64 size) {
    return static_cast<u64>(~0L >> (numBits<u64>() - size));
}

template <typename T, size_t offset, size_t size>
T getField(CompactFlight::Bits bits) noexcept {
    // TODO check
    // TODO if these bit operations are slow,
    // TODO maybe I should use my own bit struct using bitfields
    // TODO the bitset is also not packed, which wastes a lot of bytes
    // TODO but I should wait until I finish analyzing the field ranges first
    bits >>= offset;
    bits &= CompactFlight::Bits(allOnes(size));
    return static_cast<T>(bits.to_ullong());
//    return (T) ((bits >> offset) & allOnes(size)).to_ullong();
};

template <size_t offset, size_t size, typename T>
void setField(CompactFlight::Bits& bits, const T t) noexcept(false) {
    // check for overflows
    if constexpr (size < numBits<u64>()) {
        const size_t diff = numBits<u64>() - size;
        if (((t << diff) >> diff) != t) {
            std::stringstream ss;
            ss << "overflow: " << t << " does not fit in " << size << " bits";
            throw new std::overflow_error(ss.str());
        }
    }
    
    // prefer to use native bit operations
    if constexpr (offset + size <= numBits<u64>()) {
        bits |= t << (offset + size);
    } else {
        const CompactFlight::Bits tBits(t);
        bits |= tBits << (offset + size);
    }
};

template <size_t offset>
i16 CompactFlight::Side<offset>::minuteOfDay() const noexcept {
    return getField<i16, offset, TIME_BITS>(bits);
}

template <size_t offset>
i8 CompactFlight::Side<offset>::delayMinutes() const noexcept {
    return getField<i8, offset + TIME_BITS, DELAY_BITS>(bits);
}

template <size_t offset>
Time CompactFlight::Side<offset>::time() const noexcept {
    return Time(minuteOfDay());
}

template <size_t offset>
Time CompactFlight::Side<offset>::delay() const {
    return Time(delayMinutes());
}

template <size_t offset>
Time CompactFlight::Side<offset>::scheduledTime() const {
    return time() - delay();
}

template <size_t offset>
Airport CompactFlight::Side<offset>::airport() const noexcept {
    return getField<Airport, offset + TIME_BITS + DELAY_BITS, AIRPORT_BITS>(bits);
}

u16 CompactFlight::dayOfYear() const noexcept {
    return getField<u16, 0, DAY_BITS>(bits);
}

Date CompactFlight::date() const noexcept {
    return Date(dayOfYear());
}

Airline CompactFlight::airline() const noexcept {
    return getField<Airline, DAY_BITS, AIRLINE_BITS>(bits);
}

template <typename T>
constexpr T divRoundUp(const T dividend, const T divisor) {
    const std::div_t div = std::div(dividend, divisor);
    return div.quot + (div.rem != 0);
}

template <typename T>
constexpr T bitsToBytes(const T bits) {
    return divRoundUp(bits, 8);
}

template <size_t N>
union UnionBitset {
    
    // from testing, it appears the actual bits
    // are stored at the front of the std::bitset
    
    std::bitset<N> bits;
    char chars[bitsToBytes(N)];
    
    explicit UnionBitset(const std::bitset<N> bits) noexcept : bits(bits) {
    
    }
    
};

void CompactFlight::serialize(std::streambuf& buf) const noexcept {
    UnionBitset<BIT_SIZE> u(bits);
    buf.sputn(u.chars, bitsToBytes(BIT_SIZE));
}

CompactFlight::CompactFlight(const Bits bits) noexcept : bits(bits) {}

template <size_t offset>
void CompactFlight::Side<offset>::convert(Bits& bits, const RawFlight::Side& side) noexcept(false) {
    setField<offset, TIME_BITS>(bits, side.minute);
    setField<offset + TIME_BITS, DELAY_BITS>(bits, side.delay);
    setField<offset + TIME_BITS + DELAY_BITS, AIRPORT_BITS>(bits, side.airport);
}

CompactFlight::Bits CompactFlight::convert(const RawFlight& flight) noexcept(false) {
    Bits bits = 0; // TODO why can't this be bits()
    setField<0, DAY_BITS>(bits, flight.dayOfYear);
    setField<DAY_BITS, AIRLINE_BITS>(bits, flight.airline);
    Departure::convert(bits, flight.departure);
    Arrival::convert(bits, flight.arrival);
    // TODO check
    return bits;
}

CompactFlight::Bits CompactFlight::convert(std::streambuf& buf) noexcept {
    UnionBitset<BIT_SIZE> u(Bits());
    char* const chars = u.chars;
    buf.sgetn(chars, bitsToBytes(BIT_SIZE));
    return u.bits;
}

CompactFlight::CompactFlight(const RawFlight& flight) noexcept(false) : CompactFlight(convert(flight)) {}

CompactFlight::CompactFlight(std::streambuf& buf) noexcept : CompactFlight(convert(buf)) {}

Time CompactFlight::duration() const noexcept {
    return arrival().time() - departure().time();
}

Time CompactFlight::scheduledDuration() const noexcept {
    // TODO hopefully this will all be inlined, so it'll only be a bunch of arithmetic operations
    return arrival().scheduledTime() - departure().scheduledTime();
}


