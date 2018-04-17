//
// Created by Khyber on 4/15/2018.
//

#ifndef BINARYFLIGHTDELAYS_FLIGHTSINDAY_H
#define BINARYFLIGHTDELAYS_FLIGHTSINDAY_H

#include "CompactFlight.h"

namespace r3d3 {
    
    class FlightsInDay final {

    public:
        
        using size_t = u16;

    private:
        
        std::vector<CompactFlight> flights;
        
        static std::vector<CompactFlight> deserialize(std::streambuf& buf) noexcept;

    public:
        
        FlightsInDay() noexcept;
    
        explicit FlightsInDay(std::vector<CompactFlight> flights) noexcept;
    
        explicit FlightsInDay(std::streambuf& buf) noexcept;
        
        void serialize(std::streambuf& buf) const noexcept;
        
        size_t size() const noexcept;
        
        size_t numFlights() const noexcept;
        
        CompactFlight operator[](size_t i) const noexcept;
        
        CompactFlight get(size_t i) const noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_FLIGHTSINDAY_H
