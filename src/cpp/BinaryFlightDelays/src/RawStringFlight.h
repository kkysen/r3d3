//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_RAWSTRINGFLIGHT_H
#define BINARYFLIGHTDELAYS_RAWSTRINGFLIGHT_H

#include <cstddef>
#include <string>
#include <vector>

namespace r3d3 {
    
    class RawStringFlight final {
    
    public:
        
        static const size_t NUM_FIELDS = 25;
        
        const std::vector<std::string> fields;
        
        const std::string year;
        const std::string month;
        const std::string dayOfMonth;
        const std::string dayOfWeek;
        const std::string airline;
        const std::string flightNumber;
        const std::string tailNumber;
        const std::string originAirport;
        const std::string destinationAirport;
        const std::string scheduledDepartureTime; // hhmm
        const std::string departureTime; // hhmm
        const std::string departureDelay; // -m*
        const std::string taxiOut; // m*
        const std::string wheelsOff; // mmmm
        const std::string scheduledTime; // m*
        const std::string elapsedTime; // m*
        const std::string airTime; // m*
        const std::string distance; // miles
        const std::string wheelsOn; // mmmm
        const std::string taxiIn; // m*
        const std::string scheduledArrivalTime; // hhmm
        const std::string arrivalTime; // hhmm
        const std::string arrivalDelay; // -m*
        const std::string diverted; // 0|1
        const std::string cancelled; // 0|1
        
        /*
         * ignored b/c not enough data:
         *  - CANCELLATION_REASON
         *  - AIR_SYSTEM_DELAY
         *  - SECURITY_DELAY
         *  - AIRLINE_DELAY
         *  - LATE_AIRCRAFT_DELAY
         *  - WEATHER_DELAY
         */
        
        /*
         * Useful fields:
         *  - day of year
         *  - airline
         *  - origin airport
         *  - destination airport
         *  - departureTime
         *  - arrivalTime
         *  - departureDelay / elapsedTime
         *  - arrivalDelay
         */
        
        explicit RawStringFlight(std::vector<std::string> fields) noexcept;
        
        explicit RawStringFlight(std::string csvLine) noexcept;
        
        struct Side final {
            
            const std::string airport;
            const std::string scheduledTime;
            const std::string time;
            const std::string delay;
            const std::string taxi;
            const std::string wheels;
            
        };
        
        Side departure() const noexcept;
        
        Side arrival() const noexcept;
        
        bool isValid() const noexcept;
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_RAWSTRINGFLIGHT_H
