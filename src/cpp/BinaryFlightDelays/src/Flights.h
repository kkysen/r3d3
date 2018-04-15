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

namespace r3d3 {
    
    class Flights final {
    
    private:
        
        using NumDaysInYear = u16;
        
        static const NumDaysInYear DAYS_IN_YEAR = 365; // for 2015
        
        using NumFlightsInDay = u16; // large enough for num flights on every day
        
        using FlightsInDay = std::vector<CompactFlight>;
        
        static NumFlightsInDay numFlightsInDay(FlightsInDay flightsInDay);
        
        using AllFlights = std::array<FlightsInDay, DAYS_IN_YEAR>;
        
        // TODO make this a pointer and use RAII
        
        const AllFlights flights;
        
        // TODO should Array flights be passed by reference, or will copying be elided?
        
        explicit Flights(AllFlights flights) noexcept;
        
        static AllFlights toAllFlights(std::streambuf& buf) noexcept;
        
        static AllFlights toAllFlights(std::vector<RawFlight> rawFlights) noexcept;
    
    public:
        
        void serialize(std::streambuf& buf) const noexcept;
        
        explicit Flights(std::streambuf& buf) noexcept;
        
        explicit Flights(std::vector<RawFlight> rawFlights) noexcept;
    
    private:
    
        static Flights create(Blob flightsData, Blob airportsData, Blob airlinesData);
        
    public:
        
        // called by JS in fetch calls with Uint8Arrays
        static Flights jsCreate(const u8* flightsData, size_t flightsDataLength,
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
        // TODO make a separate FlightsInDay class
        
        const FlightsInDay& flightsInDay(NumDaysInYear day) const noexcept;

        FlightsInDay& flightsInDay(NumDaysInYear day) noexcept;
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_FLIGHTS_H
