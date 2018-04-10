//
// Created by Khyber on 4/6/2018.
//

#ifndef BINARYFLIGHTDELAYS_TIME_H
#define BINARYFLIGHTDELAYS_TIME_H

#include "r3d3.h"

namespace r3d3 {
    
    class Time {

    private:
    
        // signed so that it can serve as a time difference too
        const i16 minute;

    public:
        
        explicit Time(i16 minuteOfDay) noexcept;
        
        i16 minuteOfDay() const noexcept;
        
        i8 hourOfDay() const noexcept;
        
        i8 minuteOfHour() const noexcept;
        
        bool isAM() const noexcept;
        
        bool isPM() const noexcept;
        
        Time operator+(Time time) const noexcept;
        
        Time operator-(Time time) const noexcept;
        
        Time operator-() const noexcept;
    
        Time add(Time time) const noexcept;
    
        Time subtract(Time time) const noexcept;
    
        Time negate() const noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_TIME_H
