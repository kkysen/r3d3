//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_AIRLINE_H
#define BINARYFLIGHTDELAYS_AIRLINE_H

#include <istream>

#include "r3d3.h"
#include "util/DynamicEnum.h"

namespace r3d3 {
    
    class Airline final {
    
    public:
        
        using size_type = u8;
        
    private:
        
        using size_t = size_type;
        
        static const size_t NUM_AIRLINES = 14;
        
        struct Fields final {
        
        public:
            
            std::string iataCode;
            std::string name;
            
            static bool lineFilter(size_t i) noexcept;
            
            static Fields valueExtractor(std::string line) noexcept;
            
        };
        
        using Airlines = DynamicEnum<size_t, Fields>;
        
        static Airlines AIRLINES;
        
        static Map<std::string, size_t> iataMap;
        
        static void buildIataMap() noexcept;
    
        static bool initialized;
        
    public:
        
        static void init(std::istream& stream) noexcept;
        
        static void load(std::string data) noexcept;
        
        static size_t count() noexcept;
    
        static size_t numAirlines() noexcept;

    private:
        
        const size_t _index;
        
        Fields fields() const noexcept;
    
    public:
    
        explicit Airline(size_t index) noexcept;
        
        static Airline of(size_t index) noexcept;
        
        explicit Airline(std::string iataCode) noexcept;
        
        size_t index() const noexcept;
        
        std::string iataCode() const noexcept;
        
        std::string name() const noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_AIRLINE_H
