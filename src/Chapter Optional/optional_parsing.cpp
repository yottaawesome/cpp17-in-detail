// optional_parsing.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>
#include <iostream>
#include <string>

std::optional<int> ParseInt(const char* arg) {
    try {
        return { std::stoi(std::string(arg)) };
    }
    catch (...) {
        std::cerr << "cannot convert '" << arg << "' to int!\n";
    }
    
    return { };
}

int main(int argc, const char* argv[]) {
    if (argc >= 3) {
        auto oFirst = ParseInt(argv[1]);
        auto oSecond = ParseInt(argv[2]);
        
        if (oFirst && oSecond) {
            std::cout << "sum of " << *oFirst << " and " << *oSecond;
            std::cout << " is " << *oFirst + *oSecond << '\n';
        }
    }
}