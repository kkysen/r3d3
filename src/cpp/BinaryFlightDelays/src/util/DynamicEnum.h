//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_DYNAMICENUM_H
#define BINARYFLIGHTDELAYS_DYNAMICENUM_H


#include <unordered_map>
#include <istream>
#include <vector>
//#include <map>

// TODO FIXME emcc/clang can't compile <unordered_map> for some reason
#define Map std::unordered_map

namespace r3d3 {
    
    template<typename size_t, typename T = std::string>
    class DynamicEnum {
    
    public:
        
        using size_type = size_t;
        using value_type = T;
        using KeyValueMap = std::vector<T>;
        using ValueKeyMap = Map<T, size_t>;
        using LineFilter = bool (*)(const size_type) noexcept;
        using ValueExtractor = T (*)(const std::string line) noexcept;
    
    private:
        
        KeyValueMap keys;
//        ValueKeyMap values;
    
    public:
        
        DynamicEnum() noexcept;
        
        DynamicEnum(std::istream& stream, LineFilter lineFilter, ValueExtractor valueExtractor) noexcept;
        
//        static DynamicEnum<size_t, std::string> ofCsv(std::istream& stream, size_t columnNum = 0) noexcept;
        
        size_type size() const noexcept;
        
        value_type operator[](size_type i) const noexcept;
        
//        size_type operator[](value_type value) const noexcept;
        
    };
    
}

#include "DynamicEnum.tcc"

#endif //BINARYFLIGHTDELAYS_AIRLINE_H
