//
// Created by Khyber on 4/3/2018.
//

#include "utils.h"

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> vector) {
    out << "[";
    auto size = vector.size();
    if (size == 0) {
        return out << "]";
    }
    for (auto i = 0;; i++) {
        out << vector[i];
        if (i == size - 1) {
            return out << "]";
        }
        out << ", ";
    }
}