//
// Created by Khyber on 4/3/2018.
//

#ifndef BINARYFLIGHTDELAYS_FLIGHT_H
#define BINARYFLIGHTDELAYS_FLIGHT_H


#include <cstdint>
#include <string>
#include <vector>
#include <array>

typedef u8 u8;
typedef u16 u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i8 i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

class RawStringFlight {

public:
    
    using S = std::string;
    
    const S year;
    const S month;
    const S dayOfMonth;
    const S dayOfWeek;
    const S airline;
    const S flightNumber;
    const S tailNumber;
    const S originAirport;
    const S destinationAirport;
    const S scheduledDepartureTime; // hhmm
    const S departureTime; // hhmm
    const S departureDelay; // -m*
    const S taxiOut; // m*
    const S wheelsOff; // mmmm
    const S scheduledTime; // m*
    const S elapsedTime; // m*
    const S airTime; // m*
    const S distance; // miles
    const S wheelsOn; // mmmm
    const S taxiOn; // m*
    const S scheduledArrivalTime; // hhmm
    const S arrivalTime; // hhmm
    const S arrivalDelay; // -m*
    const S diverted; // 0|1
    const S cancelled; // 0|1
    
    // ignored b/c not enough data:
    //    CANCELLATION_REASON
    //    AIR_SYSTEM_DELAY
    //    SECURITY_DELAY
    //    AIRLINE_DELAY
    //    LATE_AIRCRAFT_DELAY
    //    WEATHER_DELAY
    
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
    
};

class RawFlight {

public:
    
    const i64 year;
    const i64 month;
    const i64 dayOfMonth;
    const i64 dayOfWeek;
    const std::string airline;
    const i64 flightNumber;
    const std::string tailNumber;
    const std::string originAirport;
    const std::string destinationAirport;
    const i64 scheduledDepartureTime;
    const i64 departureTime;
    const i64 departureDelay;
    const i64 taxiOut;
//    const i64 TODO

};

class CompactFlight {

private:
    
    const std::vector<bool> bits;

public:
    
    using Airline = std::array<char, 2>;
    using TailNumber = std::array<char, 6>;
    using Airport = std::array<char, 3>;
    using Time = std::array<u8, 2>;
    
    u16 year() const;
    
    u16 day() const;
    
    u8 month() const;
    
    u8 dayOfMonth() const;
    
    u8 dayOfWeek() const;
    
    u16 airlineCode() const;
    
    Airline airline() const;
    
    u16 flightNumber() const;
    
    uint32_t tailNumberCode() const;
    
    TailNumber tailNumber() const;
    
    u16 originAirportCode() const;
    
    Airport originAirport() const;
    
    u16 destinationAirportCode() const;
    
    Airport destinationAirport() const;
    
    u8 scheduledDepartureHour() const;
    
    u8 scheduledDepartureMinute() const;
    
    Time scheduledDepartureTime() const;
    
    u8 departureHour() const;
    
    u8 departureMinute() const;
    
    Time departureTime() const;
    
    i8 departureDelayMinutes() const;
    
    u8 taxiOutMinutes() const;
    
    // TODO
    
};


#endif //BINARYFLIGHTDELAYS_FLIGHT_H
