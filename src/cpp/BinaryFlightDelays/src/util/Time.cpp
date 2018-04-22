//
// Created by Khyber on 4/6/2018.
//

#include "Time.h"

namespace r3d3 {
    
    Time::Time(const i16 minuteOfDay) noexcept : minute(minuteOfDay) {}
    
    Time Time::of(i16 minuteOfDay) noexcept {
        return Time(minuteOfDay);
    }
    
    i16 Time::minuteOfDay() const noexcept {
        return minute;
    }
    
    i8 Time::hourOfDay() const noexcept {
        return static_cast<i8>(minuteOfDay() / 60);
    }
    
    i8 Time::minuteOfHour() const noexcept {
        return static_cast<i8>(minuteOfDay() % 60);
    }
    
    bool Time::isAM() const noexcept {
        return !isPM();
    }
    
    bool Time::isPM() const noexcept {
        // & 1 converts 24:00 to AM
        return static_cast<bool>((hourOfDay() / 12) & 1);
    }
    
    Time Time::operator+(Time time) const noexcept {
        return Time(minute + time.minute);
    }
    
    Time Time::operator-(Time time) const noexcept {
        return Time(minute - time.minute);
    }
    
    Time Time::operator-() const noexcept {
        return Time(-minute);
    }
    
    Time Time::add(const Time time) const noexcept {
        return *this + time;
    }
    
    Time Time::subtract(r3d3::Time time) const noexcept {
        return *this - time;
    }
    
    Time Time::negate() const noexcept {
        return -*this;
    }
    
    #define MAKE_CMP(cmp) \
    bool operator cmp(const Time time1, const Time time2) noexcept { \
        return time1.minute cmp time2.minute; \
    }
    
    MAKE_CMP(==)
    MAKE_CMP(!=)
    MAKE_CMP(<)
    MAKE_CMP(>)
    MAKE_CMP(<=)
    MAKE_CMP(>=)
    
    #undef MAKE_CMP
    
    Time Time::between(const Time first, const Time last) noexcept {
        Time diff = last - first;
        if (first > last) {
            diff = -diff;
        }
        return diff;
    }
    
    std::ostream& operator<<(std::ostream& out, const Time time) noexcept {
        return out << i32(time.hourOfDay())
                   << ":" << i32(time.minuteOfHour());
    }
    
};