//
// Created by Khyber on 4/11/2018.
//

#ifndef BINARYFLIGHTDELAYS_BLOB_H
#define BINARYFLIGHTDELAYS_BLOB_H

#include "../r3d3.h"

namespace r3d3 {
    
    struct Blob final {
    
    public:
        
        const u8* const data;
        const size_t length;
        
        static Blob ofString(std::string data);
        
        const char* charData() const noexcept;
        
        std::string toString() const noexcept;
        
        std::stringbuf toStringBuf() const noexcept;
        
//        std::istream toInputStream() const noexcept;
        
        void init(void (* init)(std::istream& stream)) const noexcept;
        
        static void load(std::string data, void (* init)(std::istream& stream)) noexcept;
        
    };
    
}

#endif //BINARYFLIGHTDELAYS_BLOB_H
