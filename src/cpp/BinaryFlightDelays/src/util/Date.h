//
// Created by Khyber on 4/6/2018.
//

#ifndef BINARYFLIGHTDELAYS_DATE_H
#define BINARYFLIGHTDELAYS_DATE_H

#include "../r3d3.h"

namespace r3d3 {
    
    class Date final {
    
    private:
        
        static const u16 YEAR = 2015;
        
        u16 day;
    
    public:
        
        explicit Date(u16 dayOfYear) noexcept;
        
        static Date of(u16 dayOfYear) noexcept;
        
        tm time() const noexcept;
        
        // [2015, 2015]
        u16 year() const noexcept;
        
        // [0, 364]
        u16 dayOfYear() const noexcept;
    
    private:
        
        // [0, 365], 0 = March 1
        i32 offsetDayOfYear() const noexcept;
        
        // [0, 11], 0 = March
        i32 offsetMonth() const noexcept;
    
    public:
        
        // [0, 11]
        u8 month() const noexcept;
        
        // [1, 31]
        u8 dayOfMonth() const noexcept;
        
        // [0, 52]
        u8 week() const noexcept;
        
        // [0, 6], 0 = Sunday
        u8 dayOfWeek() const noexcept;
        
        friend std::ostream& operator<<(std::ostream& out, Date date) noexcept;
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_DATE_H
