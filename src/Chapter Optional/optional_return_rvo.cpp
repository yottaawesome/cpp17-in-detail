// optional_return_rvo.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <string>
#include <optional>

std::optional<std::string> TryParse(std::string input) {
    if (!input.empty())
        return input;
        
    return std::nullopt;
}

std::optional<std::string> TryParseNrvo(std::string input) {
    std::optional<std::string> oOut; // empty
    
    std::cout << &oOut << '\n';
    
    if (!input.empty())
        oOut = input;
        
    return oOut;
}

int main()
{
    auto oOut = TryParse("Hello");
    std::cout << &oOut << '\n';
    
    auto oOutNrvo = TryParseNrvo("Hello");
    std::cout << &oOutNrvo << '\n';
}