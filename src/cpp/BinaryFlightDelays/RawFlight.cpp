//
// Created by Khyber on 4/5/2018.
//

#include "RawFlight.h"

using namespace r3d3;

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
    return {
            .minute = hourMinuteToMinuteOfDay(std::stoll(side.time)),
            .delay = std::stoll(side.delay),
            .airport = AIRPORTS[side.airport],
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
            .airline = AIRLINES[flight.airline],
            .departure = Side(flight.departure()),
            .arrival = Side(flight.arrival()),
    };
}

#define MAKE_FIELD(name) \
            (Field) {#name, [](const RawFlight flight) { return static_cast<i64>(flight.name); }}

const std::vector<RawFlight::Field> RawFlight::FIELDS = {
        MAKE_FIELD(dayOfYear),
        MAKE_FIELD(airline),
        MAKE_FIELD(departure.minute),
        MAKE_FIELD(departure.delay),
        MAKE_FIELD(departure.airport),
        MAKE_FIELD(arrival.minute),
        MAKE_FIELD(arrival.delay),
        MAKE_FIELD(arrival.airport),
};

#undef MAKE_FIELD

std::vector<RawFlight::AnalyzedField>
RawFlight::analyzeFieldRanges(std::istream& stream, std::vector<RawFlight::Field> fields) noexcept {
    {
        std::string firstLine;
        std::getline(stream, firstLine);
    }
    
    std::vector<RawFlight> flights;
    for (std::string line; std::getline(stream, line);) {
        flights.push_back(RawFlight(RawStringFlight(line)));
    }
    
    const auto numFields = fields.size();
    std::vector<AnalyzedField> analyzedFields;
    analyzedFields.reserve(numFields);
    for (auto i = 0; i < numFields; i++) {
        const Field field = fields[i];
        const AnalyzedField analyzedField = {
                .field = field,
                .range = NumberRange::ofValues<RawFlight>(flights, field.mapper),
        };
        analyzedFields.push_back(analyzedField);
    }
    return analyzedFields;
}

std::vector<RawFlight::AnalyzedField>
RawFlight::analyzeFieldRanges(const std::string path, const std::vector<Field> fields) noexcept(false) {
    return analyzeFieldRanges(openFile(path), fields);
}

const std::vector<RawFlight::AnalyzedField> RawFlight::FIELD_RANGES = analyzeFieldRanges();

std::ostream& r3d3::operator<<(std::ostream& out, RawFlight::Field field) noexcept {
    return out << "Field[" << field.name << "]";
}

std::ostream& r3d3::operator<<(std::ostream& out, RawFlight::AnalyzedField analyzedField) noexcept {
    return out <<
               analyzedField.field << ": "
               << analyzedField.range << ", "
               << "numBits: " << analyzedField.range.toNumBits();
}

std::ostream& r3d3::operator<<(std::ostream& out, std::vector<RawFlight::AnalyzedField> analyzedFields) noexcept {
    for (const auto analyzedField : analyzedFields) {
        out << analyzedField;
    }
}