#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <sstream>

#include "DsvMissingDataStats.h"
//#include "utils.h"

#define p(x) std::cout << #x << ": " << (x) << std::endl

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> vector) {
    out << "[";
    auto size = vector.size();
    if (size == 0) {
        return out << "]";
    }
    for (auto i = 0;; i++) {
        out << vector[i];
        if (i == size - 1) {
            return out << "]";
        }
        out << ", ";
    }
}

typedef std::unordered_map<std::string, std::string> Args;

Args parseArgs(const int argc, const char* const* const argv) {
    std::unordered_map<std::string, std::string> args;
    for (auto i = 1; i < argc; i++) {
        const std::string arg(argv[i]);
        const size_t splitIndex = arg.find('=');
        if (splitIndex == -1) {
            continue;
        }
        const std::string key = arg.substr(0, splitIndex);
        const std::string value = arg.substr(splitIndex + 1, arg.length());
        args[key] = value;
    }
    return args;
};

template<typename T>
std::vector<T> parseArray(const std::string s) {
    if (s.length() < 2 || s[0] != '[' || s[s.length() - 1] != ']') {
        std::cout << "invalid array: " << s << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<T> vector;
    std::stringstream ss(s.substr(1, s.length() - 1));
    T t;
    ss >> t;
    if (ss) {
        vector.push_back(t);
        char delim;
        while (ss >> delim >> t && delim == ',') {
            vector.push_back(t);
        }
    }
    if (ss) {
        std::cout << "invalid array: " << s << std::endl;
        exit(EXIT_FAILURE);
    }
    return vector;
}

template<size_t N>
void checkRequiredArgs(const Args args, const std::array<std::string, N> requiredArgs) {
    bool einval = false;
    for (const std::string requiredArg : requiredArgs) {
        if (args.count(requiredArg) == 0) {
            einval = true;
            std::cout << "missing required arg: " << requiredArg << std::endl;
        }
    }
    if (einval) {
        exit(EXIT_FAILURE);
    }
}

int main(const int argc, const char* const* const argv) {
    if (argc == 1) {
        std::cout
                << "Usage: "
                << "./" << argv[0] << " "
                << "path=[csv file]" << ", "
                << "[ignoreColumns=[a, b, c]]" << ", "
                << "[ignoreRows=[a, b, c]]"
                << std::endl;
        return EXIT_FAILURE;
    }
    
    Args args = parseArgs(argc, argv);
    
    const std::array requiredArgs = {std::string("path")};
    checkRequiredArgs(args, requiredArgs);
    
    const std::string path = args[std::string("path")];
    
    std::unordered_map<std::string, std::vector<size_t>> ignored {
            {"ignoreColumns", std::vector<size_t>()},
            {"ignoreRows",    std::vector<size_t>()}
    };
    
    for (auto& entry : ignored) {
        const std::string key = entry.first;
        if (args.count(key) > 0) {
            std::vector<size_t> values = parseArray<size_t>(args[key]);
            for (auto i = 0; i < values.size(); i++) {
                values[i]--;
            }
            entry.second = values;
        }
    }
    
    const DsvMissingDataStats stats = DsvMissingDataStats::ofCsvFile(
            DsvMissingDataStats::FileArgs(path, ignored["ignoreColumns"], ignored["ignoreRows"]));
    
    std::cout << "\n\n" << stats.toString() << std::endl;
    
    return EXIT_SUCCESS;
}