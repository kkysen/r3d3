//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_DYNAMICENUM_H
#define BINARYFLIGHTDELAYS_DYNAMICENUM_H


#include <unordered_map>
#include <fstream>
#include <vector>

namespace r3d3 {
    
    template<typename size_t, typename T = std::string>
    class DynamicEnum {
    
    public:
        
        using size_type = size_t;
        using value_type = T;
        using KeyValueMap = std::vector<T>;
        using ValueKeyMap = std::unordered_map<T, size_t>;
        using LineFilter = bool (*)(const size_type) noexcept;
        using ValueExtractor = T (*)(const std::string line) noexcept;
    
    private:
        
        KeyValueMap keys;
        ValueKeyMap values;
    
    public:
        
        DynamicEnum(std::istream& stream, LineFilter lineFilter, ValueExtractor valueExtractor) noexcept;
        
        DynamicEnum(std::string path, LineFilter lineFilter, ValueExtractor valueExtractor) noexcept(false);
        
        static DynamicEnum<size_t, std::string> ofCsv(std::istream& stream, size_t columnNum = 0) noexcept;
        
        static DynamicEnum<size_t, std::string> ofCsv(std::string path, size_t columnNum = 0) noexcept(false);
        
        size_type size() const noexcept;
        
        value_type operator[](size_type i) const noexcept;
        
        size_type operator[](value_type value) const noexcept;
        
    };
    
}

#endif //BINARYFLIGHTDELAYS_AIRLINE_H
