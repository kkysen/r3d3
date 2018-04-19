//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_FLIGHTS_H
#define BINARYFLIGHTDELAYS_FLIGHTS_H

#include <array>
#include <streambuf>
#include <future>

#include "CompactFlight.h"
#include "util/Blob.h"
#include "FlightsInDay.h"

namespace r3d3 {
    
    class Flights final {

    public:
    
        using size_t = u16;
    
        static const size_t DAYS_IN_YEAR = 365; // for 2015
    
    private:
        
        using AllFlights = std::array<FlightsInDay, DAYS_IN_YEAR>;
        
        const AllFlights flights;
    
        const std::size_t _numFlights;
        
        static std::size_t countNumFlights(AllFlights flights) noexcept;
        
        explicit Flights(AllFlights flights) noexcept;
        
        static AllFlights deserialize(std::streambuf& buf) noexcept;
        
        static AllFlights toAllFlights(std::vector<RawFlight> rawFlights) noexcept;
    
    public:
        
        void serialize(std::streambuf& buf) const noexcept;
        
        explicit Flights(std::streambuf& buf) noexcept;
        
        explicit Flights(std::vector<RawFlight> rawFlights) noexcept;
        
        // called by JS in fetch calls with Uint8Arrays
    
        static Flights create(std::string flightsData) noexcept;
        
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
        // TODO make a separate FlightsInDay class
        
        size_t size() const noexcept;
        
        size_t numDays() const noexcept;
        
        std::size_t numFlights() const noexcept;
        
        FlightsInDay operator[](size_t day) const noexcept;
        
        FlightsInDay get(size_t day) const noexcept;
        
        CompactFlight flight(size_t day, size_t i) const noexcept;
        
        double totalDistance() const noexcept;
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_FLIGHTS_H
