// emplace_return.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <vector>
#include <string>

int main() {
    std::vector<std::string> stringVector;
    
    // in C++11/14:
    stringVector.emplace_back("Hello");
    stringVector.back().append("World");
    
    // in C++17:
    stringVector.emplace_back("Hello").append("World");
}