// optional_reset.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>
#include <iostream>

int main() {
    std::optional<int> oEmpty;
    std::optional<int> oTwo(2);
    std::optional<int> oTen(10);
    
    std::cout << std::boolalpha;
    std::cout << (oTen > oTwo) << '\n';
    std::cout << (oTen < oTwo) << '\n';
    std::cout << (oEmpty < oTwo) << '\n';
    std::cout << (oEmpty == std::nullopt) << '\n';
    std::cout << (oTen == 10) << '\n';
}