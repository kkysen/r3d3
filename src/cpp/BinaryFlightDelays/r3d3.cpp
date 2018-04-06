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
void put(std::streambuf& buf, const T t) noexcept {
    union {
        T t;
        char chars[sizeof(T)];
    } u;
    u.t = t;
    buf.sputn(u.chars, sizeof(T));
}

template <typename T>
T get(std::streambuf& buf) noexcept {
    union {
        T t;
        char chars[sizeof(T)];
    } u;
    buf.sgetn(u.chars, sizeof(T));
    return u.t;
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