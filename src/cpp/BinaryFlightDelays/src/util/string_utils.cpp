//
// Created by Khyber on 4/12/2018.
//

#include "string_utils.h"

namespace r3d3 {
    
    size_t findNth(const std::string s, const char search, size_t n, size_t start) noexcept {
        while (n > 0) {
            const size_t i = s.find(search, start);
            if (n == 0 || i == std::string::npos) {
                return i;
            }
            start = i + 1;
            n--;
        }
        return s.find(search, start);
    }
    
    std::string splitIndex(const std::string s, const char delimiter, const size_t index) noexcept {
        if (index == 0) {
            const size_t end = findNth(s, delimiter, index);
            return end == std::string::npos ? s : s.substr(0, end);
        }
        const size_t start = findNth(s, delimiter, index - 1) + 1; // + 1 to skip delim
        const size_t end = s.find(delimiter, start);
        return s.substr(start, end);
    }
    
};