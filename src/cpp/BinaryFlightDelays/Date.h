//
// Created by Khyber on 4/6/2018.
//

#ifndef BINARYFLIGHTDELAYS_DATE_H
#define BINARYFLIGHTDELAYS_DATE_H

#include "r3d3.h"

namespace r3d3 {
    
    class Date final {

    private:
        
        static const u16 YEAR = 2015;
        
        const u16 day;

    public:
        
        explicit Date(u16 dayOfYear) noexcept;
        
        tm time() const noexcept;
        
        u16 year() const noexcept;
        
        u16 dayOfYear() const noexcept;
        
        u8 month() const noexcept;
        
        u8 dayOfMonth() const noexcept;
        
        u8 week() const noexcept;
        
        u8 dayOfWeek() const noexcept;
        
    };
    
};


#endif //BINARYFLIGHTDELAYS_DATE_H
