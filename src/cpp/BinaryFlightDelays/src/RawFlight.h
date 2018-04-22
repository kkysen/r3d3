//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_RAWFIELD_H
#define BINARYFLIGHTDELAYS_RAWFIELD_H

#include "r3d3.h"
#include "RawStringFlight.h"
#include "util/NumberRange.h"
#include "Airport.h"
#include "Airline.h"

namespace r3d3 {
    
    class RawFlight final {
    
    public:
        
        class Side final {
        
        private:
            
            struct Args final {
                
                i64 minute;
                i64 delay;
                Airport airport;
                
            };
        
        public:
            
            const i64 minute;
            const i64 delay;
            const Airport airport;
            
            explicit Side(Args args) noexcept;
            
            explicit Side(const RawStringFlight::Side& side) noexcept;
            
            static Args convert(const RawStringFlight::Side& side) noexcept;
            
        };
        
        const i64 dayOfYear;
        const Airline airline;
        
        const Side departure;
        const Side arrival;
    
    private:
        
        struct Args final {
            
            i64 dayOfYear;
            Airline airline;
            
            Side departure;
            Side arrival;
            
        };
    
    public:
        
        explicit RawFlight(Args args) noexcept;
        
        explicit RawFlight(const RawStringFlight& flight) noexcept;
        
        static Args convert(const RawStringFlight& flight) noexcept;
        
        struct Field final {
            
            using Mapper = i64 (*)(RawFlight flight) noexcept;
            
            const std::string name;
            const Mapper mapper;
            
            friend std::ostream& operator<<(std::ostream& out, Field field) noexcept;
            
        };
        
        static const std::vector<Field> FIELDS;
        
        struct AnalyzedField final {
            
            const Field field;
            const NumberRange range;
            
            friend std::ostream& operator<<(std::ostream& out, AnalyzedField analyzedField) noexcept;
            
        };
        
        static std::vector<RawFlight> readFlights(std::istream& stream) noexcept;
        
        static std::vector<AnalyzedField> analyzeFieldRanges(
                std::istream& stream, std::vector<Field> fields = FIELDS) noexcept;
        
//        static const std::vector<AnalyzedField> FIELD_RANGES;
        
        friend std::ostream& operator<<(std::ostream& out, std::vector<AnalyzedField> analyzedFields) noexcept;
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_RAWFIELD_H
