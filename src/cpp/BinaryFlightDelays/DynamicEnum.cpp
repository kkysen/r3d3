//
// Created by Khyber on 4/5/2018.
//

#include "DynamicEnum.h"
#include "r3d3.h"

using namespace r3d3;

template <typename size_t, typename T>
DynamicEnum<size_t, T>::DynamicEnum(std::istream& stream, const LineFilter lineFilter,
                                    const ValueExtractor valueExtractor) {
    size_t lineNum = 0;
    size_t enumNum = 0;
    for (std::string line; std::getline(stream, line); lineNum++) {
        if (!lineFilter(lineNum)) {
            continue;
        }
        const T value = valueExtractor(line);
        keys.push_back(value);
        keys[enumNum] = value;
        values[value] = enumNum++;
        enumNum++;
    }
}

template <typename size_t, typename T>
DynamicEnum<size_t, T>::DynamicEnum(const std::string path, const LineFilter lineFilter,
                                    const ValueExtractor valueExtractor)
        : DynamicEnum(openFile(path), lineFilter, valueExtractor) {}

//template<>
//using size_t = std::string::size_type;
size_t findNth(const std::string s, const char search, size_t n, size_t start = 0) noexcept {
    while (n > 0) {
        const size_t i = s.find(search, start);
        if (n == 0 || i == std::string::npos) {
            return i;
        }
        start = i + 1;
        n--;
    }
}

//template<>
//using size_t = std::string::size_type;
std::string splitIndex(const std::string s, const char delimiter, const size_t index) noexcept {
    if (index == 0) {
        const size_t end = findNth(s, delimiter, index);
        return end == std::string::npos ? s : s.substr(0, end);
    }
    const size_t start = findNth(s, delimiter, index - 1) + 1; // + 1 to skip delim
    const size_t end = s.find(delimiter, start);
    return s.substr(start, end);
}

template <typename size_t>
DynamicEnum<size_t, std::string> DynamicEnum<size_t, std::string>::ofCsv(std::istream& stream, const size_t columnNum) noexcept {
    const LineFilter lineFilter = [](const size_t i) noexcept -> bool {
        return i > 0;
    };
    const ValueExtractor keyExtractor = [columnNum](const std::string line) noexcept -> std::string {
        return splitIndex(line, ',', columnNum);
    };
    return DynamicEnum<size_t, std::string>(stream, lineFilter, keyExtractor);
}

template <typename size_t, typename T>
DynamicEnum<size_t, T> DynamicEnum<size_t, T>::ofCsv(const std::string path, const size_t columnNum) noexcept(false) {
    return ofCsv(openFile(path), columnNum);
}

template <typename size_t, typename T>
size_t DynamicEnum<size_t, T>::size() const noexcept {
    return keys.size();
}

template <typename size_t, typename T>
T DynamicEnum<size_t, T>::operator[](const size_t i) const noexcept {
    return keys[i];
}

template <typename size_t, typename T>
size_t DynamicEnum<size_t, T>::operator[](const T value) const noexcept {
    return values[value];
}
