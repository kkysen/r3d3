//
// Created by Khyber on 4/5/2018.
//

#include "DynamicEnum.h"

#include "../r3d3.h"

namespace r3d3 {
    
    template <typename size_t, typename T>
    DynamicEnum<size_t, T>::DynamicEnum() noexcept {}
    
    template <typename size_t, typename T>
    DynamicEnum<size_t, T>::DynamicEnum(std::istream& stream, const LineFilter lineFilter,
                                        const ValueExtractor valueExtractor) noexcept {
        size_t lineNum = 0;
        size_t enumNum = 0;
        for (std::string line; std::getline(stream, line); lineNum++) {
            if (!lineFilter(lineNum)) {
                continue;
            }
            const T value = valueExtractor(line);
            keys.push_back(value);
            keys[enumNum] = value;
//        values[value] = enumNum++;
            enumNum++;
        }
    }

//template <typename size_t>
//DynamicEnum<size_t, std::string> DynamicEnum<size_t, std::string>::ofCsv(std::istream& stream, const size_t columnNum) noexcept {
//    const LineFilter lineFilter = [](const size_t i) noexcept -> bool {
//        return i > 0;
//    };
//    const ValueExtractor keyExtractor = [columnNum](const std::string line) noexcept -> std::string {
//        return splitIndex(line, ',', columnNum);
//    };
//    return DynamicEnum<size_t, std::string>(stream, lineFilter, keyExtractor);
//}
    
    template <typename size_t, typename T>
    size_t DynamicEnum<size_t, T>::size() const noexcept {
        return keys.size();
    }
    
    template <typename size_t, typename T>
    T DynamicEnum<size_t, T>::operator[](const size_t i) const noexcept {
        return keys[i];
    }

//template <typename size_t, typename T>
//size_t DynamicEnum<size_t, T>::operator[](const T value) const noexcept {
//    return values[value];
//}

};