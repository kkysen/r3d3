//
// Created by Khyber on 4/6/2018.
//

#include <iostream>
#include "Date.h"

namespace r3d3 {
    
    Date::Date(const u16 dayOfYear) noexcept : day(dayOfYear) {}
    
    Date Date::of(u16 dayOfYear) noexcept {
        return Date(dayOfYear);
    }
    
    tm Date::time() const noexcept {
        tm time = {};
        time.tm_year = year() - 1900;
        time.tm_mon = month();
        time.tm_mday = dayOfMonth();
        mktime(&time);
        return time;
    }
    
    u16 Date::year() const noexcept {
        return YEAR;
    }
    
    u16 Date::dayOfYear() const noexcept {
        return day;
    }
    
    // returns day of year start from March, 1 in range [0, 365]
    i32 Date::offsetDayOfYear() const noexcept {
        return (dayOfYear() + 365 - 31 - 28) % 365;
    }
    
    // returns month starting from March in range [0, 11]
    i32 Date::offsetMonth() const noexcept {
        // see http://howardhinnant.github.io/date_algorithms.html#civil_from_days
        return (5 * offsetDayOfYear() + 2) / 153;
    }
    
    u8 Date::month() const noexcept {
        // see http://howardhinnant.github.io/date_algorithms.html#civil_from_days
        const i32 mp = offsetMonth(); // [0, 11], 0 = March
        const i32 m = mp + (mp < 10 ? 3 : -9); // [1, 12], 1 = January
        return static_cast<u8>((m - 1) % 12);
    }
    
    u8 Date::dayOfMonth() const noexcept {
        // see http://howardhinnant.github.io/date_algorithms.html#civil_from_days
        return static_cast<u8>(offsetDayOfYear() - (153 * offsetMonth() + 2) / 5 + 1);
    }
    
    u8 Date::week() const noexcept {
        return static_cast<u8>(dayOfYear() / 7);
    }
    
    u8 Date::dayOfWeek() const noexcept {
        return static_cast<u8>(time().tm_wday);
    }
    
    std::ostream& operator<<(std::ostream& out, const Date date) noexcept {
        return out << u32(date.month() + 1)
                   << "/" << u32(date.dayOfMonth())
                   << "/" << u32(date.year());
    }
    
};