//
// Created by Khyber on 4/5/2018.
//

#include <iostream>
#include "RawFlight.h"

namespace r3d3 {
    
    RawFlight::Side::Side(const RawFlight::Side::Args args) noexcept
            : minute(args.minute), delay(args.delay), airport(args.airport) {}
    
    RawFlight::Side::Side(const RawStringFlight::Side& side) noexcept
            : Side(convert(side)) {}
    
    // hourMinute of form hhmm
    i64 hourMinuteToMinuteOfDay(const i64 hourMinute) noexcept {
        const i64 hour = hourMinute / 100;
        const i64 minute = hourMinute % 100;
        return hour * 60 + minute;
    }
    
    RawFlight::Side::Args RawFlight::Side::convert(const RawStringFlight::Side& side) noexcept {
//        try {
//            i64 time = std::stoll(side.time);
//        } catch (const std::invalid_argument& e) {
//            p(e.what());
//        }
        return {
                .minute = hourMinuteToMinuteOfDay(std::stoll(side.time)),
                .delay = std::stoll(side.delay),
                .airport = Airport(side.airport),
        };
    }
    
    RawFlight::RawFlight(const RawFlight::Args args) noexcept
            : dayOfYear(args.dayOfYear), airline(args.airline),
              departure(args.departure), arrival(args.arrival) {}
    
    RawFlight::RawFlight(const RawStringFlight& flight) noexcept
            : RawFlight(convert(flight)) {}
    
    i64 dayOfMonthToYear(const i64 year, const i64 month, const i64 dayOfMonth) noexcept {
        tm time = {};
        time.tm_year = static_cast<int>(year - 1900);
        time.tm_mon = static_cast<int>(month - 1);
        time.tm_mday = static_cast<int>(dayOfMonth);
        mktime(&time);
        return time.tm_yday;
    }
    
    RawFlight::Args RawFlight::convert(const RawStringFlight& flight) noexcept {
        return {
                .dayOfYear = dayOfMonthToYear(
                        std::stoll(flight.year),
                        std::stoll(flight.month),
                        std::stoll(flight.dayOfMonth)
                ),
                .airline = Airline(flight.airline),
                .departure = Side(flight.departure()),
                .arrival = Side(flight.arrival()),
        };
    }
    
    std::vector<RawFlight> RawFlight::readFlights(std::istream& stream) noexcept {
        {
            std::string firstLine;
            std::getline(stream, firstLine);
        }
        
        size_t lineNum = 0;
        std::vector<RawFlight> flights;
        for (std::string line; std::getline(stream, line); lineNum++) {
            if (lineNum % 100000 == 0) {
                p(lineNum);
            }
//            if (lineNum > 1e5) {
//                break;
//            }
            const RawStringFlight flight(line);
            if (flight.isValid()) {
                flights.push_back(RawFlight(flight));
            } else {
                // TODO maybe nothing or print
            }
        }
        return flights;
    }

#define MAKE_FIELD(name) \
            (Field) {#name, [](const RawFlight flight) noexcept -> i64 { return static_cast<i64>(flight.name); }}
    
    const std::vector<RawFlight::Field> RawFlight::FIELDS = {
    #ifndef __EMSCRIPTEN__
            MAKE_FIELD(dayOfYear),
            MAKE_FIELD(airline.index()),
            MAKE_FIELD(departure.minute),
            MAKE_FIELD(departure.delay),
            MAKE_FIELD(departure.airport.index()),
            MAKE_FIELD(arrival.minute),
            MAKE_FIELD(arrival.delay),
            MAKE_FIELD(arrival.airport.index()),
    #endif
    };

#undef MAKE_FIELD
    
    std::vector<RawFlight::AnalyzedField> RawFlight::analyzeFieldRanges(
            std::istream& stream, std::vector<RawFlight::Field> fields) noexcept {
        const auto flights = readFlights(stream);
        const size_t numFields = fields.size();
        std::vector<AnalyzedField> analyzedFields;
        analyzedFields.reserve(numFields);
        for (size_t i = 0; i < numFields; i++) {
            const Field field = fields[i];
            std::cout << "analyzing: " << field << std::endl;
            const AnalyzedField analyzedField = {
                    .field = field,
                    .range = NumberRange::ofValues<RawFlight>(flights, field.mapper),
            };
            analyzedFields.push_back(analyzedField);
        }
        return analyzedFields;
    }

//const std::vector<RawFlight::AnalyzedField> RawFlight::FIELD_RANGES = analyzeFieldRanges();
    
    std::ostream& operator<<(std::ostream& out, RawFlight::Field field) noexcept {
        return out << "Field[" << field.name << "]";
    }
    
    std::ostream& operator<<(std::ostream& out, RawFlight::AnalyzedField analyzedField) noexcept {
        return out <<
                   analyzedField.field << ": "
                   << analyzedField.range << ", "
                   << "numBits: " << static_cast<u32>(analyzedField.range.toNumBits());
    }
    
    std::ostream& operator<<(std::ostream& out, std::vector<RawFlight::AnalyzedField> analyzedFields) noexcept {
        for (const auto analyzedField : analyzedFields) {
            out << analyzedField;
        }
        return out;
    }
    
};