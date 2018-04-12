//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_AIRPORT_H
#define BINARYFLIGHTDELAYS_AIRPORT_H

#include "r3d3.h"
#include "GeoLocation.h"

namespace r3d3 {
    
    class Airport final {
    
    public:
        
        using size_type = u16;
        
        static const std::string FILE_NAME = "airports.csv";
        
        static const std::string PATH = r3d3::DIR + FILE_NAME;
    
    private:
        
        using size_t = size_type;
    
        static const size_t NUM_AIRPORTS = 322;
        
        struct Fields final {
        
        public:
            
            const std::string iataCode;
            const std::string name;
            
            const std::string city;
            const std::string state;
            const std::string country;
            
            const GeoLocation location;
            
            static bool lineFilter(size_t i) noexcept;
            
            static Fields valueExtractor(std::string line) noexcept;
            
        };
        
        using Airports = DynamicEnum<size_t, Fields>;
        
        static const Airports AIRPORTS;
    
        static double distances[NUM_AIRPORTS][NUM_AIRPORTS];
    
        static void calculateDistances() noexcept;

    public:
        
        static bool initialized = false;
        
        static void init(std::istream& stream) noexcept;
    
        static size_t numAirports() const noexcept;

    private:
        
        const size_t _index;
        
        Fields fields() const noexcept;
    
    public:
    
        explicit Airport(size_t index) noexcept;
        
        size_t index() const noexcept;
        
        std::string iataCode() const noexcept;
        
        std::string name() const noexcept;
        
        std::string city() const noexcept;
    
        std::string state() const noexcept;
    
        std::string country() const noexcept;
        
        GeoLocation location() const noexcept;
        
        double distanceTo(Airport airport) const noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_AIRPORT_H
