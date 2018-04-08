//
// Created by Khyber on 4/6/2018.
//

#include "Date.h"

using namespace r3d3;

Date::Date(const u16 dayOfYear) noexcept : day(dayOfYear) {}

tm Date::time() const noexcept {
    tm time = {};
    time.tm_yday = dayOfYear();
    time.tm_year = year() - 1900;
    mktime(&time);
    return time;
}

u16 Date::year() const noexcept {
    return YEAR;
}

u16 Date::dayOfYear() const noexcept {
    return day;
}

u8 Date::month() const noexcept {
    return static_cast<u8>(time().tm_mon);
}

u8 Date::dayOfMonth() const noexcept {
    return static_cast<u8>(time().tm_mday);
}

u8 Date::week() const noexcept {
    return static_cast<u8>(dayOfYear() / 52);
}

u8 Date::dayOfWeek() const noexcept {
    return static_cast<u8>(time().tm_wday);
}
