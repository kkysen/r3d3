//
// Created by Khyber on 4/5/2018.
//

#include "r3d3.h"

#include <algorithm>
#include <fstream>
#include <cstring>

namespace r3d3 {
    
    std::ostream& operator<<(std::ostream& out, const u8 i) noexcept {
        return out << static_cast<u32>(i);
    }
    
    std::ostream& operator<<(std::ostream& out, const i8 i) noexcept {
        return out << static_cast<i32>(i);
    }
    
    void checkFile(const std::istream& stream) noexcept(false) {
        if (!stream) {
            throw std::ifstream::failure(strerror(errno));
        }
    }
    
    std::unique_ptr<std::istream> openFile(const std::string path) noexcept(false) {
        std::istream* const file = new std::ifstream(path);
        checkFile(*file);
        return std::unique_ptr<std::istream>(file);
    }
    
    std::vector<std::string> readLines(std::istream& stream) noexcept {
        std::vector<std::string> lines;
        for (std::string line; std::getline(stream, line);) {
            lines.push_back(line);
        }
        return lines;
    }
    
    std::vector<std::string> readLines(std::string path) noexcept(false) {
        return readLines(*openFile(path));
    }
    
    std::vector<std::string> split(const std::string s, const char delimiter) noexcept {
        const size_t numTokens = 1 + static_cast<const size_t>(std::count(s.begin(), s.end(), delimiter));
        if (numTokens == 0) {
            return std::vector<std::string>();
        }
        size_t prev = 0;
        size_t pos = 0;
        std::vector<std::string> tokens;
        tokens.reserve(numTokens);
        for (size_t i = 0; i < numTokens - 1; i++) {
            pos = s.find(delimiter, prev);
            tokens.push_back(s.substr(prev, pos - prev));
            prev = pos + sizeof(delimiter);
        }
        tokens.push_back(s.substr(prev, s.length()));
        return tokens;
    }
    
};