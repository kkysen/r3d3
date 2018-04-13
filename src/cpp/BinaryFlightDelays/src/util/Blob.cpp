//
// Created by Khyber on 4/11/2018.
//

#include "Blob.h"

namespace r3d3 {
    
    const char* Blob::charData() const noexcept {
        return reinterpret_cast<const char*>(data);
    }
    
    std::string Blob::toString() const noexcept {
        return std::string(charData(), length);
    }
    
    std::stringbuf Blob::toStringBuf() const noexcept {
        return std::stringbuf(toString());
    }

//std::istream Blob::toInputStream() const noexcept {
//    std::stringbuf buf = toStringBuf();
//    return std::istream(&buf);
//}
    
    void Blob::initUsingInputStream(void (* init)(std::istream&)) const noexcept {
        std::stringbuf buf = toStringBuf();
        std::istream stream(&buf);
        init(stream);
    }
    
};