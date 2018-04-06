//
// Created by Khyber on 4/5/2018.
//

#include <algorithm>
#include "RawStringFlight.h"

using namespace r3d3;

RawStringFlight::RawStringFlight(const std::vector<std::string> fields) noexcept :
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

std::vector<std::string> split(const std::string s, const char delimiter) noexcept {
    const size_t numTokens = static_cast<const size_t>(std::count(s.begin(), s.end(), delimiter));
    if (numTokens == 0) {
        return std::vector<std::string>();
    }
    size_t prev = 0;
    size_t pos = 0;
    std::vector<std::string> tokens;
    tokens.reserve(numTokens);
    for (auto i = 0; i < numTokens - 1; i++) {
        pos = s.find(delimiter, prev);
        tokens.push_back(s.substr(prev, pos - prev));
        prev = pos + sizeof(delimiter);
    }
    tokens.push_back(s.substr(prev, s.length()));
    return tokens;
}

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