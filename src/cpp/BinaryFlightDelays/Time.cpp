//
// Created by Khyber on 4/6/2018.
//

#include "Time.h"

using namespace r3d3;

Time::Time(i16 minuteOfDay) noexcept : minute(minuteOfDay) {}

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
