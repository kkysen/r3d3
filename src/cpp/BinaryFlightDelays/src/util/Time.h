//
// Created by Khyber on 4/6/2018.
//

#ifndef BINARYFLIGHTDELAYS_TIME_H
#define BINARYFLIGHTDELAYS_TIME_H

#include "../r3d3.h"

namespace r3d3 {
    
    class Time final {

    private:
    
        // signed so that it can serve as a time difference too
        i16 minute;

    public:
        
        explicit Time(i16 minuteOfDay) noexcept;
        
        static Time of(i16 minuteOfDay) noexcept;
        
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
        
        template <typename T>
        Time operator*(T scale) const noexcept;
    
        #define MAKE_CMP(cmp) \
        friend bool operator cmp(Time time1, Time time2) noexcept
        
        MAKE_CMP(==);
        MAKE_CMP(!=);
        MAKE_CMP(<);
        MAKE_CMP(>);
        MAKE_CMP(<=);
        MAKE_CMP(>=);
    
        #undef MAKE_CMP
        
        static Time between(Time start, Time end) noexcept;
        
        friend std::ostream& operator<<(std::ostream& out, Time time) noexcept;
        
    };
    
};

#include "Time.tcc"

#endif //BINARYFLIGHTDELAYS_TIME_H
