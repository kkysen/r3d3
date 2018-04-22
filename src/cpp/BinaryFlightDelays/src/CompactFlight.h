//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_COMPACTFLIGHT_H
#define BINARYFLIGHTDELAYS_COMPACTFLIGHT_H

#include <bitset>
#include <streambuf>

#include "r3d3.h"
#include "RawFlight.h"
#include "util/Date.h"
#include "util/Time.h"
#include "Airport.h"
#include "Airline.h"
#include "util/Color.h"
#include "util/Vector.h"

namespace r3d3 {
    
    class CompactFlight final {
    
    private:
    
    public:
    
        class Interpolator final {
    
        public:
        
            struct State final {

            public:
    
                f32 opacity; // 1 to 0 and back to 1
                Vector position;
                Color color;
                
                friend std::ostream& operator<<(std::ostream& out, State state) noexcept;
            
            };
    
        private:
        
            u32 _duration;
            f32 time; // TODO check should I use time passed from attrTween()
        
            Vector start;
            Vector displacement;
            
            Color startColor;
            Color endColor;
            
            f32 minOpacity;
        
            State _state;
            
            // state will be read immediately after update()
            // safe b/c JS is single-threaded and
            static State sharedState;
            
            f32 tick() const noexcept;
            
            f32 interpolateOpacityLinear(f32 x) const noexcept;
            
            f32 interpolateOpacityQuadratic(f32 x) const noexcept;
    
        public:
        
            // opacity ignored
            Interpolator(u32 duration, State start, State end) noexcept;
        
            static constexpr u32 stateSize() noexcept;
        
            static constexpr State* state() noexcept;
            
            static uintptr_t statePointer() noexcept;
        
            u32 duration() const noexcept;
        
            void interpolate(const f32 time) noexcept;
            
            void update() noexcept;
        
        };
        
        class Side final {
            
            friend CompactFlight;
        
        private:
            
            static const size_t TIME_BITS = 11;
            static const size_t DELAY_BITS = 12;
            static const size_t AIRPORT_BITS = 9;
            
            static const i16 DELAY_OFFSET = -87; // min delay of all flights
            
            #pragma pack(push, 1)
            
            struct Bits final {
                
                u16 time: TIME_BITS;
                u16 delay: DELAY_BITS;
                Airport::size_type airport: AIRPORT_BITS;
                
            };
            
            #pragma pack(pop)
            
            Bits bits;
            
            i16 minuteOfDay() const noexcept;
            
            i16 delayMinutes() const noexcept;
        
        public:
            
            Time time() const noexcept;
            
            Time scheduledTime() const noexcept;
            
            Time delay() const noexcept;
            
            Airport airport() const noexcept;
            
            Interpolator::State interpolatorState() const noexcept;
        
        private:
            
            explicit Side(Bits bits) noexcept;
            
            static Bits convert(const RawFlight::Side& side) noexcept(false);
            
            explicit Side(const RawFlight::Side& side) noexcept(false);
            
        };
    
    public:
        
        using Departure = Side;
        using Arrival = Side;
    
    private:
        
        static const size_t DAY_BITS = 9;
        static const size_t AIRLINE_BITS = 4;
        
        #pragma pack(push, 1)
        
        struct Bits final {
            
            u16 day: DAY_BITS;
            Airline::size_type airline: AIRLINE_BITS;
            
            Departure departure;
            Arrival arrival;
            
        };
        
        #pragma pack(pop)
        
        Bits bits;
        
        u16 dayOfYear() const noexcept;
    
    public:
        
        Date date() const noexcept;
        
        Airline airline() const noexcept;
        
        Departure departure() const noexcept;
        
        Arrival arrival() const noexcept;
        
        Time duration() const noexcept;
        
        Time scheduledDuration() const noexcept;
        
        double distance() const noexcept; // meters
        
        void serialize(std::streambuf& buf) const noexcept;
    
    private:
        
        explicit CompactFlight(Bits bits) noexcept;
        
        static Bits convert(const RawFlight& flight) noexcept(false);
        
        static Bits convert(std::streambuf& buf) noexcept;
    
    public:
        
        explicit CompactFlight(const RawFlight& flight) noexcept(false);
        
        explicit CompactFlight(std::streambuf& buf) noexcept;
    
    private:
        
        using Projection = void (*)() noexcept;
        
        static Projection projection;
        
        static GeoLocation _projectedLocation;
    
        static Vector project(GeoLocation location) noexcept;
    
    public:
    
        static constexpr size_t projectedLocationSize() noexcept;
    
        static constexpr GeoLocation* projectedLocation() noexcept;
        
        static uintptr_t projectedLocationPointer() noexcept;
        
        static void setProjection(Projection projection) noexcept;
        
        static void setProjectionPointer(uintptr_t projectionPointer) noexcept;
        
        void render() const noexcept;
        
        bool tryRender(Time time) const noexcept;
        
        bool isRenderable() const noexcept;
        
        Interpolator interpolator() const noexcept;
        
    };
    
};

#include "CompactFlight.tcc"

#endif //BINARYFLIGHTDELAYS_COMPACTFLIGHT_H
