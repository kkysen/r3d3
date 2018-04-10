//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_AIRLINE_H
#define BINARYFLIGHTDELAYS_AIRLINE_H

#include "r3d3.h"

namespace r3d3 {
    
    class Airline {
    
    public:
        
        using size_type = u8;
        
        static const std::string FILE_NAME = "airlines.csv";
        
        static const std::string PATH = r3d3::DIR + FILE_NAME;
    
    private:
        
        using size_t = size_type;
        
        static const size_t NUM_AIRLINES = 14;
        
        struct Fields {
        
        public:
            
            const std::string iataCode;
            const std::string name;
            
            static bool lineFilter(size_t i) noexcept;
            
            static Fields valueExtractor(std::string line) noexcept;
            
        };
        
        using Airlines = DynamicEnum<size_t, Fields>;
        
        static const Airlines AIRLINES;
        
        const size_t _index;
        
        Fields fields() const noexcept;
    
    public:
        
        static size_t numAirlines() const noexcept ;
    
        explicit Airline(size_t index) noexcept;
        
        size_t index() const noexcept;
        
        std::string iataCode() const noexcept;
        
        std::string name() const noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_AIRLINE_H
