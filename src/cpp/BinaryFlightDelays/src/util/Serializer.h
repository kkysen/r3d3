//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_SERIALIZER_H
#define BINARYFLIGHTDELAYS_SERIALIZER_H

#include <streambuf>

namespace r3d3 {
    
    template <typename T>
    union Serializer final {
        
        T value;
        char chars[sizeof(value)];
        
        Serializer() noexcept;
        
        explicit Serializer(T value) noexcept;
        
        static void put(std::streambuf& buf, T value) noexcept;
        
        static T get(std::streambuf& buf) noexcept;
        
    };
    
};

#include "Serializer.tcc"

#endif //BINARYFLIGHTDELAYS_SERIALIZER_H
