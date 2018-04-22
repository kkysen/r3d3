//
// Created by Khyber on 4/5/2018.
//

#include <cstdlib>
#include <limits>
#include <sstream>
#include <cmath>

#include "CompactFlight.h"
#include "util/Serializer.h"

namespace r3d3 {
    
    
    
    // CompactFlight::Interpolator
    
    CompactFlight::Interpolator::Interpolator(const u32 duration, const State start, const State end) noexcept :
            _duration(duration),
            time(0),
            start(start.position),
            displacement(end.position - start.position),
            startColor(start.color),
            endColor(end.color),
            minOpacity(0.5),
            _state(start) {
        _state.opacity = 1;
        sharedState = _state;
//        pf();
//        p(_state);
    }
    
    CompactFlight::Interpolator::State CompactFlight::Interpolator::sharedState = {
            .opacity = 1,
            .position = {0, 0},
            .color = {0, 0, 0},
    };
    
    uintptr_t CompactFlight::Interpolator::statePointer() noexcept {
        return reinterpret_cast<uintptr_t>(state());
    }
    
    u32 CompactFlight::Interpolator::duration() const noexcept {
        return _duration;
    }
    
    f32 CompactFlight::Interpolator::tick() const noexcept {
        return 1.0f / _duration;
    }
    
    f32 CompactFlight::Interpolator::interpolateOpacityLinear(const f32 x) const noexcept {
        return std::abs(2 / minOpacity * x - 1);
    }
    
    f32 CompactFlight::Interpolator::interpolateOpacityQuadratic(const f32 x) const noexcept {
        const f32 y = (2 / minOpacity * x - 1);
        return y * y;
    }
    
    Color mixDelayColors(f32 weight) noexcept {
        return Color::mix(weight, Color::RED, Color::GREEN);
    }
    
    f32 delayWeight(const Time delay) noexcept {
        // TODO delay might be negative if flight left early
        return delay.minuteOfDay() / 30.0f; // TODO for now
    }
    
    Color delayColor(const Time delay) noexcept {
        return mixDelayColors(delayWeight(delay));
    }
    
    u32 scaleDuration(const Time duration) noexcept {
        return static_cast<u32>(duration.minuteOfDay()) * 10; // TODO for now
    }
    
    void CompactFlight::Interpolator::interpolate(const f32 time) noexcept {
        _state.opacity = interpolateOpacityQuadratic(time);
        _state.position = start + displacement * time;
        _state.color = Color::mix(time, startColor, endColor);
        sharedState = _state;
    }
    
    void CompactFlight::Interpolator::update() noexcept {
        interpolate(time);
        time += tick();
        if (u32(time * _duration) % 100 == 0) {
//            p(_state);
        }
    }
    
    std::ostream& operator<<(std::ostream& out, const CompactFlight::Interpolator::State state) noexcept {
        return out << "["
                   "position: " << state.position << ", "
                   << "color: " << state.color.rgbString() << ", "
                   << "opacity: " << state.opacity
                << "]";
    }
    
    
    
    // CompactFlight::Side constructors and deserialization
    
    CompactFlight::Side::Side(const Bits bits) noexcept : bits(bits) {}
    
    CompactFlight::Side::Bits CompactFlight::Side::convert(const RawFlight::Side& side) noexcept(false) {
        return {
                .time = narrowCast<u16, TIME_BITS>(side.minute),
                .delay = narrowCast<u16, DELAY_BITS>(side.delay - DELAY_OFFSET),
                .airport = narrowCast<Airport::size_type, AIRPORT_BITS>(side.airport.index()),
        };
    }
    
    CompactFlight::Side::Side(const RawFlight::Side& side) noexcept(false) : Side(convert(side)) {}
    
    
    
    // CompactFlight constructors, deserialization, and serialization
    
    CompactFlight::CompactFlight(const Bits bits) noexcept : bits(bits) {}
    
    CompactFlight::Bits CompactFlight::convert(const RawFlight& flight) noexcept(false) {
        return {
                .day = narrowCast<u16, DAY_BITS>(flight.dayOfYear),
                .airline = narrowCast<Airline::size_type, AIRLINE_BITS>(flight.airline.index()),
                .departure = Departure(flight.departure),
                .arrival = Arrival(flight.arrival),
        };
    }
    
    CompactFlight::CompactFlight(const RawFlight& flight) noexcept(false) : CompactFlight(convert(flight)) {}
    
    CompactFlight::Bits CompactFlight::convert(std::streambuf& buf) noexcept {
        return Serializer<Bits>::get(buf);
    }
    
    CompactFlight::CompactFlight(std::streambuf& buf) noexcept : CompactFlight(convert(buf)) {}
    
    void CompactFlight::serialize(std::streambuf& buf) const noexcept {
        Serializer<Bits>::put(buf, bits);
    }
    
    
    
    // CompactFlight::Side bit accessors
    
    i16 CompactFlight::Side::minuteOfDay() const noexcept {
        return bits.time;
    }
    
    i16 CompactFlight::Side::delayMinutes() const noexcept {
        return bits.delay + DELAY_OFFSET;
    }
    
    Airport CompactFlight::Side::airport() const noexcept {
        return Airport(bits.airport);
    }
    
    
    
    // CompactFlight bit accessors
    
    u16 CompactFlight::dayOfYear() const noexcept {
        return bits.day;
    }
    
    Airline CompactFlight::airline() const noexcept {
        return Airline(bits.airline);
    }
    
    
    
    // CompactFlight::Side methods
    
    Time CompactFlight::Side::time() const noexcept {
        return Time(minuteOfDay());
    }
    
    Time CompactFlight::Side::delay() const noexcept {
        return Time(delayMinutes());
    }
    
    Time CompactFlight::Side::scheduledTime() const noexcept {
        return time() - delay();
    }
    
    CompactFlight::Interpolator::State CompactFlight::Side::interpolatorState() const noexcept {
        return {
                .opacity = 1,
                .position = project(airport().location()),
                .color = delayColor(delay()),
        };
    }
    
    
    
    // CompactFlight methods
    
    Date CompactFlight::date() const noexcept {
        return Date(dayOfYear());
    }
    
    Time CompactFlight::duration() const noexcept {
        return Time::between(departure().time(), arrival().time());
    }
    
    Time CompactFlight::scheduledDuration() const noexcept {
        return Time::between(departure().scheduledTime(), arrival().scheduledTime());
    }
    
    double CompactFlight::distance() const noexcept {
        // method call distanceTo() allows Airport to possibly cache distances in whatever way
        return departure().airport().distanceTo(arrival().airport());
    }
    
    
    
    // subclass accessors
    
    CompactFlight::Departure CompactFlight::departure() const noexcept {
        return Departure(bits.departure);
    }
    
    CompactFlight::Arrival CompactFlight::arrival() const noexcept {
        return Arrival(bits.arrival);
    }
    
    CompactFlight::Interpolator CompactFlight::interpolator() const noexcept {
        return Interpolator(scaleDuration(duration()),
                            departure().interpolatorState(), arrival().interpolatorState());
    }
    
    
    
    // Projection
    
    GeoLocation CompactFlight::_projectedLocation = GeoLocation(0, 0);
    
    uintptr_t CompactFlight::projectedLocationPointer() noexcept {
        return reinterpret_cast<uintptr_t>(projectedLocation());
    }
    
    void CompactFlight::setProjection(Projection projection) noexcept {
        CompactFlight::projection = projection;
    }
    
    void CompactFlight::setProjectionPointer(uintptr_t projectionPointer) noexcept {
        setProjection(reinterpret_cast<Projection>(projectionPointer));
    }
    
    Vector CompactFlight::project(GeoLocation location) noexcept {
        _projectedLocation = location;
//        pf();
//        p(_projectedLocation);
        projection();
//        p(_projectedLocation);
        return {
                .x = static_cast<f32>(_projectedLocation.longitude()),
                .y = static_cast<f32>(_projectedLocation.latitude())
        };
    }
    
    // default for debug
    CompactFlight::Projection CompactFlight::projection = // NOLINT
            []() noexcept -> void {
                std::cout << "CompactFlight::projection not set yet: "
                          << _projectedLocation
                          << std::endl;
            };

//    // default for debug
//    CompactFlight::Renderer CompactFlight::renderer = // NOLINT
//            [](const u32 duration,
//               const f64 startX, const f64 startY, const std::string startColor,
//               const f64 endX, const f64 endY, const std::string endColor) noexcept -> void {
//                std::cout << "CompactFlight::renderer not set yet: "
//                          << "\n\t" << "duration: " << duration
//                          << "\n\t" << "start: (" << startX << ", " << startY << "), " << startColor
//                          << "\n\t" << "end: (" << endX << ", " << endY << "), " << endColor
//                          << std::endl;
//            };
    
    void CompactFlight::render() const noexcept {
        // TODO
    }
    
    bool CompactFlight::tryRender(const Time time) const noexcept {
        if (departure().time() != time) {
            return false;
        }
        render();
        return true;
    }
    
    bool CompactFlight::isRenderable() const noexcept {
        return !project(departure().airport().location()).hasNaN()
               && !project(arrival().airport().location()).hasNaN();
    }
    
};