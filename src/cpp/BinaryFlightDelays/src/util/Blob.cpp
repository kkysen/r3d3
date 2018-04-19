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
    
    void Blob::init(void (* init)(std::istream&)) const noexcept {
        std::stringbuf buf = toStringBuf();
        std::istream stream(&buf);
        init(stream);
    }
    
    Blob Blob::ofString(std::string data) {
        return {
                .data = reinterpret_cast<const u8*>(data.c_str()),
                .length = data.length(),
        };
    }
    
    void Blob::load(const std::string data, void (* const init)(std::istream&)) noexcept {
        ofString(data).init(init);
    }
    
};