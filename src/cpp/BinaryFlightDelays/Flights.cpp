//
// Created by Khyber on 4/5/2018.
//

#include "Flights.h"

#include <sstream>
#include <cstring>

using namespace r3d3;

Flights::NumFlightsInDay Flights::numFlightsInDay(Flights::FlightsInDay flightsInDay) {
    return static_cast<NumFlightsInDay>(flightsInDay.size());
}

Flights::Flights(Flights::Array flights) noexcept
        : flights(flights) {}

Flights::Array Flights::convert(std::streambuf& buf) noexcept {
    Array flights;
    for (auto i = 0; i < flights.size(); i++) {
        const NumFlightsInDay numFlightInDay = r3d3::get<NumFlightsInDay>(buf);
        FlightsInDay flightsInDay;
        flightsInDay.reserve(numFlightInDay);
        for (auto j = 0; j <  numFlightInDay; j++) {
            flightsInDay.push_back(CompactFlight(buf));
        }
    }
    return flights;
}

std::streambuf& Flights::convert(const emscripten_fetch_t& fetch) noexcept {
    // TODO check copy and move constructors
    std::string data(fetch.data, fetch.numBytes);
    std::stringbuf buf(data, std::ios_base::in);
    return buf;
}

void Flights::serialize(std::streambuf& buf) const noexcept {
    for (const auto flightsInDay : flights) {
        put(buf, numFlightsInDay(flightsInDay));
        for (const auto flight : flightsInDay) {
            flight.serialize(buf);
        }
    }
}

Flights::Flights(std::streambuf& buf) noexcept
        : Flights(convert(buf)) {}

Flights::Flights(const emscripten_fetch_t& fetch) noexcept
        : Flights(convert(fetch)) {}

using OnFetch = void (*)(emscripten_fetch_t* fetch) noexcept;
using OnFetchRef = void (*)(const emscripten_fetch_t& fetch) noexcept;

OnFetch convertOnFetch(OnFetchRef onFetch) noexcept {
    return [](emscripten_fetch_t* fetch) {
        onFetch(*fetch);
    };
}

void Flights::load(const std::string url) noexcept {
    startedLoading = true;
    
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = static_cast<u32>(EMSCRIPTEN_FETCH_LOAD_TO_MEMORY)
                      | static_cast<u32>(EMSCRIPTEN_FETCH_PERSIST_FILE);
    
    attr.onsuccess = convertOnFetch([](const emscripten_fetch_t& fetch) noexcept {
        promise.set_value(Flights(fetch));
    });
    
    attr.onerror = convertOnFetch([url](const emscripten_fetch_t& fetch) noexcept {
        promise.set_exception(std::runtime_error("fetch: " + url));
    });
    
    emscripten_fetch(&attr, url.c_str());
}

std::future<const Flights&> Flights::get(const std::string url) noexcept {
    if (!startedLoading) {
        // concurrency not an issue b/c only one thread in JS
        load(url);
    }
    return promise.get_future();
}