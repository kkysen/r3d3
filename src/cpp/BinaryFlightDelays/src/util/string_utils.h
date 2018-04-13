//
// Created by Khyber on 4/12/2018.
//

#ifndef BINARYFLIGHTDELAYS_STRING_UTILS_H
#define BINARYFLIGHTDELAYS_STRING_UTILS_H

#include <string>

namespace r3d3 {
    
    size_t findNth(std::string s, char search, size_t n, size_t start = 0) noexcept;
    
    std::string splitIndex(std::string s, char delimiter, size_t index) noexcept;
    
};

#endif //BINARYFLIGHTDELAYS_STRING_UTILS_H
