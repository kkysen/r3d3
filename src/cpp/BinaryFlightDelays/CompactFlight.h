//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_COMPACTFLIGHT_H
#define BINARYFLIGHTDELAYS_COMPACTFLIGHT_H

#include <bitset>
#include <streambuf>

#include <emscripten/bind.h>

#include "r3d3.h"
#include "RawFlight.h"
#include "Date.h"
#include "Time.h"

namespace r3d3 {
    
    class CompactFlight final {
    
    private:
        
        static const size_t OWN_BYTE_SIZE = 3;
        static const size_t SIDE_BYTE_SIZE = 5;
        static const size_t BYTE_SIZE = OWN_BYTE_SIZE + 2 * SIDE_BYTE_SIZE;
        
        // these are generous bit sizes
        // after analysis, overlapping bytes can be compressed into more saved bits
        static const size_t OWN_BIT_SIZE = OWN_BYTE_SIZE * 8;
        static const size_t SIDE_BIT_SIZE = SIDE_BYTE_SIZE * 8;
        static const size_t BIT_SIZE = BYTE_SIZE * 8;
        
        static const size_t DAY_BITS = 16;
        static const size_t AIRLINE_BITS = 8;
    
    public:
        
        using Bits = std::bitset<BIT_SIZE>;
        
        static const u16 YEAR = 2015;
        
        template <size_t offset>
        class Side final {
            
            friend CompactFlight;
        
        private:
            
            static const size_t TIME_BITS = 16;
            static const size_t DELAY_BITS = 8;
            static const size_t AIRPORT_BITS = 16;
            
            i16 minuteOfDay() const noexcept;
            
            i8 delayMinutes() const noexcept; // i8 might exclude a couple flights
        
        public:
            
            Time time() const noexcept;
            
            Time scheduledTime() const noexcept;
            
            Time delay() const noexcept;
            
            Airport airport() const noexcept;
            
            std::string airportName() const noexcept;
        
        private:
            
            const Bits bits;
            
            explicit Side(Bits bits) noexcept;
            
            static void convert(Bits& bits, const RawFlight::Side& side) noexcept(false);
            
        };

    private:
        
        u16 dayOfYear() const noexcept;
    
    public:
        
        using Departure = Side<OWN_BIT_SIZE + 0 * SIDE_BIT_SIZE>;
        using Arrival = Side<OWN_BIT_SIZE + 1 * SIDE_BIT_SIZE>;
        
        Date date() const noexcept;
        
        Airline airline() const noexcept;
        
        std::string airlineName() const noexcept;
        
        Departure departure() const noexcept;
        
        Arrival arrival() const noexcept;
        
        Time duration() const noexcept;
        
        Time scheduledDuration() const noexcept;
        
        double distance() const noexcept; // miles
        
        void serialize(std::streambuf& buf) const noexcept;
    
    private:
        
        explicit CompactFlight(Bits bits) noexcept;
        
        static Bits convert(const RawFlight& flight) noexcept(false);
        
        static Bits convert(std::streambuf& buf) noexcept;
    
    public:
        
        explicit CompactFlight(const RawFlight& flight) noexcept(false);
        
        explicit CompactFlight(std::streambuf& buf) noexcept;
    
    private:
        
        const Bits bits;
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_COMPACTFLIGHT_H
