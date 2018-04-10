//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_COMPACTFLIGHT_H
#define BINARYFLIGHTDELAYS_COMPACTFLIGHT_H

#include <bitset>
#include <streambuf>

#include "r3d3.h"
#include "RawFlight.h"
#include "Date.h"
#include "Time.h"
#include "Airport.h"
#include "Airline.h"

namespace r3d3 {
    
    class CompactFlight final {
    
    private:
    
    public:
        
        class Side final {
            
            friend CompactFlight;
        
        private:
            
            static const size_t TIME_BITS = 11;
            static const size_t DELAY_BITS = 12;
            static const size_t AIRPORT_BITS = 9;
            
            static const i16 DELAY_OFFSET = -87; // min delay of all flights
    
            #pragma pack(push, 1)
            
            struct Bits {
                
                const u16 time: TIME_BITS;
                const u16 delay: DELAY_BITS;
                const Airport::size_type airport: AIRPORT_BITS;
                
            };
    
            #pragma pack(pop)
            
            const Bits bits;
            
            i16 minuteOfDay() const noexcept;
            
            i16 delayMinutes() const noexcept;
        
        public:
            
            Time time() const noexcept;
            
            Time scheduledTime() const noexcept;
            
            Time delay() const noexcept;
            
            Airport airport() const noexcept;
            
        private:
            
            explicit Side(Bits bits) noexcept;
            
            static Bits convert(const RawFlight::Side& side) noexcept(false);
            
            explicit Side(const RawFlight::Side& side) noexcept(false);
            
        };
    
    public:
        
        using Departure = Side;
        using Arrival = Side;
    
    private:
        
        static const size_t DAY_BITS = 9;
        static const size_t AIRLINE_BITS = 4;
        
        #pragma pack(push, 1)
        
        struct Bits {
            
            const u16 day: DAY_BITS;
            const Airline::size_type airline: AIRLINE_BITS;
            
            const Departure departure;
            const Arrival arrival;
            
        };
        
        #pragma pack(pop)
        
        const Bits bits;
        
        u16 dayOfYear() const noexcept;
    
    public:
        
        Date date() const noexcept;
        
        Airline airline() const noexcept;
        
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
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_COMPACTFLIGHT_H
