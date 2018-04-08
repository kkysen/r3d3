//
// Created by Khyber on 4/5/2018.
//

#include "r3d3.h"

template<typename T>
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

template<typename T, size_t N>
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
constexpr size_t r3d3::numBits() {
    return (size_t) std::numeric_limits<T>::digits;
}

template <typename Target, size_t bitSize, typename Source>
Target r3d3::narrowCast(const Source source) {
    struct Bits {
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

std::istream& openFile(const std::string path) noexcept(false) {
    std::ifstream file(path);
    if (!file) {
        throw std::ifstream::failure(path);
    }
    return file;
}

std::vector<std::string> readLines(std::istream& stream) noexcept {
    std::vector<std::string> lines;
    for (std::string line; std::getline(stream, line);) {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> readLines(std::string path) noexcept(false) {
    return readLines(openFile(path));
}