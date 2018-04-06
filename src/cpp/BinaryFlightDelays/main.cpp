#include <iostream>
#include <fstream>

#include "flight.h"
#include "RawFlight.h"

int main() {
    const std::string path = "../../../data/flight-delays/flights.csv";
//    system("pwd");
//    const std::string path = "main.cpp";
    std::ifstream file(path);
    if (!file) {
        throw std::ifstream::failure(path);
    }
    std::string line;
    std::getline(file, line);
    std::getline(file, line);
    std::cout << line << std::endl;
    const r3d3::RawStringFlight flight(line);
    std::cout << "Hello, World!" << std::endl;
    std::cout << flight.airline << std::endl;
    
    {
        using namespace r3d3; // for operator<< overload
        std::cout << r3d3::RawFlight::FIELD_RANGES << std::endl;
    }
    
    return 0;
}