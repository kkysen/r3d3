//
// Created by Khyber on 4/5/2018.
//

#include <algorithm>
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

std::vector<std::string> split(const std::string s, const char delimiter) noexcept {
    const size_t numTokens = static_cast<const size_t>(std::count(s.begin(), s.end(), delimiter));
    if (numTokens == 0) {
        return std::vector<std::string>();
    }
    size_t prev = 0;
    size_t pos = 0;
    std::vector<std::string> tokens;
    tokens.reserve(numTokens);
    for (auto i = 0; i < numTokens - 1; i++) {
        pos = s.find(delimiter, prev);
        tokens.push_back(s.substr(prev, pos - prev));
        prev = pos + sizeof(delimiter);
    }
    tokens.push_back(s.substr(prev, s.length()));
    return tokens;
}

std::streambuf& convert(const emscripten_fetch_t& fetch) noexcept {
    // TODO check copy and move constructors
    std::string data(fetch.data, fetch.numBytes);
    std::stringbuf buf(data, std::ios_base::in);
    return buf;
}