// to_chars_basic.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <charconv> // from_chars, to_chars
#include <string>

int main() {
    std::string str { "xxxxxxxx" };
    const int value = 1986;
 
    const auto res = std::to_chars(str.data(), str.data() + str.size(), value);
    if (res.ec == std::errc()) {
        std::cout << str << ", filled: " << res.ptr - str.data() << " characters\n";
    }
    else {
        std::cout << "value too large!\n";
    }
}
