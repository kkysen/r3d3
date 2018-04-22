//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_AIRPORT_H
#define BINARYFLIGHTDELAYS_AIRPORT_H

#include "r3d3.h"
#include "util/GeoLocation.h"
#include "util/DynamicEnum.h"

namespace r3d3 {
    
    class Airport final {
    
    public:
        
        using size_type = u16;
        
    private:
        
        using size_t = size_type;
    
        static const size_t NUM_AIRPORTS = 322;
        
        struct Fields final {
        
        public:
            
            std::string iataCode;
            std::string name;
            
            std::string city;
            std::string state;
            std::string country;
            
            GeoLocation location;
            
            static bool lineFilter(size_t i) noexcept;
            
            static Fields valueExtractor(std::string line) noexcept;
            
        };
        
        using Airports = DynamicEnum<size_t, Fields>;
        
        static Airports AIRPORTS;
        
        static Map<std::string, size_t> iataMap;
        
        static void buildIataMap() noexcept;
        
        static double distances[NUM_AIRPORTS][NUM_AIRPORTS];
    
        static void calculateDistances() noexcept;
    
        static bool initialized;
        
    public:
        
        static void init(std::istream& stream) noexcept;
    
        static void load(std::string data) noexcept;
    
        static size_t count() noexcept;
        
        static size_t numAirports() noexcept;

    private:
        
        const size_t _index;
        
        Fields fields() const noexcept;
    
    public:
    
        explicit Airport(size_t index) noexcept;
        
        static Airport of(size_t index) noexcept;
        
        explicit Airport(std::string iataCode) noexcept;

        static Airport ofIataCode(std::string iataCode) noexcept;
        
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
