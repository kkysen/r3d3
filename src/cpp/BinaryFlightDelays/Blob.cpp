//
// Created by Khyber on 4/11/2018.
//

#include "Blob.h"

using namespace r3d3;

char* Blob::charData() const noexcept {
    return static_cast<char*>(data);
}

std::string Blob::toString() const noexcept {
    return std::string(charData(), length);
}

std::stringbuf Blob::toStringBuf() const noexcept {
    return std::stringbuf(toString());
}

std::istream Blob::toInputStream() const noexcept {
    std::stringbuf buf = toStringBuf();
    return std::istream(&buf);
}

void Blob::initUsingInputStream(void (* init)(std::istream&)) const noexcept {
    std::istream stream = toInputStream();
    init(stream);
}
