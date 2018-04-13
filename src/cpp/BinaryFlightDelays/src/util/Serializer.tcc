//
// Created by Khyber on 4/8/2018.
//

#include <iostream>
#include "Serializer.h"

namespace r3d3 {
    
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
    
    template <typename T>
    Serializer<T>::Serializer() noexcept {}
    
    template <typename T>
    Serializer<T>::Serializer(const T value) noexcept : value(value) {}
    
    template <typename T>
    void Serializer<T>::put(std::streambuf& buf, const T value) noexcept {
        Serializer u(value);
        buf.sputn(u.chars, sizeof(T));
    }
    
    template <typename T>
    T Serializer<T>::get(std::streambuf& buf) noexcept {
        Serializer u;
        buf.sgetn(u.chars, sizeof(T));
        return u.value;
    }
    
};