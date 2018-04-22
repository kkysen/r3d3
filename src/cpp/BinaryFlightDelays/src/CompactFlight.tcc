//
// Created by Khyber on 4/21/2018.
//

#include "CompactFlight.h"

namespace r3d3 {
    
    constexpr u32 CompactFlight::Interpolator::stateSize() noexcept {
        return sizeof(State);
    }
    
    constexpr CompactFlight::Interpolator::State* CompactFlight::Interpolator::state() noexcept {
        return &sharedState;
    }
    
    
    
    constexpr size_t CompactFlight::projectedLocationSize() noexcept {
        return sizeof(_projectedLocation);
    }
    
    constexpr GeoLocation* CompactFlight::projectedLocation() noexcept {
        return &_projectedLocation;
    }
    
}