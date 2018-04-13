//
// Created by Khyber on 4/12/2018.
//

#include "r3d3.h"

namespace r3d3 {
    
    template <typename T>
    std::ostream& operator<<(std::ostream& out, const std::vector<T> a) noexcept {
        out << "[";
        const auto size = a.size();
        if (size == 0) {
            return out << "]";
        }
        for (auto i = 0;; i++) {
            out << a[i];
            if (i == size - 1) {
                return out << "]";
            }
            out << ", ";
        }
    }
    
    template <typename T, size_t N>
    std::ostream& operator<<(std::ostream& out, const std::array<T, N> a) noexcept {
        out << "[";
        const auto size = a.size();
        if (size == 0) {
            return out << "]";
        }
        for (auto i = 0;; i++) {
            out << a[i];
            if (i == size - 1) {
                return out << "]";
            }
            out << ", ";
        }
    }
    
    template <typename T>
    constexpr size_t numBits() {
        return (size_t) std::numeric_limits<T>::digits;
    }
    
    template <typename Target, size_t bitSize, typename Source>
    Target narrowCast(const Source source) {
        struct Bits final {
            Target value: bitSize;
        };
        Bits bits = {.value = static_cast<Target>(source)};
        if (bits.value != source) {
            std::stringstream ss;
            ss << "overflow: " << source << " (" << numBits<Source>() << ")"
               << " does not fit in " << bitSize << " bits";
            throw new std::overflow_error(ss.str());
        }
        return bits.value;
    }
    
}