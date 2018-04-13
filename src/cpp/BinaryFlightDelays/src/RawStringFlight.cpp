//
// Created by Khyber on 4/5/2018.
//

#include "RawStringFlight.h"

#include "r3d3.h"

namespace r3d3 {
    
    RawStringFlight::RawStringFlight(const std::vector<std::string> fields) noexcept :
            fields(fields.begin(), fields.begin() + 24),
            year(fields[0]),
            month(fields[1]),
            dayOfMonth(fields[2]),
            dayOfWeek(fields[3]),
            airline(fields[4]),
            flightNumber(fields[5]),
            tailNumber(fields[6]),
            originAirport(fields[7]),
            destinationAirport(fields[8]),
            scheduledDepartureTime(fields[9]),
            departureTime(fields[10]),
            departureDelay(fields[11]),
            taxiOut(fields[12]),
            wheelsOff(fields[13]),
            scheduledTime(fields[14]),
            elapsedTime(fields[15]),
            airTime(fields[16]),
            distance(fields[17]),
            wheelsOn(fields[18]),
            taxiIn(fields[19]),
            scheduledArrivalTime(fields[20]),
            arrivalTime(fields[21]),
            arrivalDelay(fields[22]),
            diverted(fields[23]),
            cancelled(fields[24]) {}
    
    RawStringFlight::RawStringFlight(const std::string csvLine) noexcept
            : RawStringFlight(split(csvLine, ',')) {}
    
    RawStringFlight::Side RawStringFlight::departure() const noexcept {
        return {
                .airport = originAirport,
                .scheduledTime = scheduledDepartureTime,
                .time = departureTime,
                .delay = departureDelay,
                .taxi = taxiOut,
                .wheels = wheelsOff,
        };
    }
    
    RawStringFlight::Side RawStringFlight::arrival() const noexcept {
        return {
                .airport = destinationAirport,
                .scheduledTime = scheduledArrivalTime,
                .time = scheduledTime,
                .delay = arrivalDelay,
                .taxi = taxiIn,
                .wheels = wheelsOn,
        };
    }
    
    bool RawStringFlight::isValid() const noexcept {
        for (auto field : fields) {
            if (field.empty()) {
                return false;
            }
        }
        return true;
    }
    
};