// from_chars_basic.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <charconv> // from_chars, to_chars
#include <string>

int main() {
    const std::string str { "12345678901234" };
    int value = 0;
    const auto res = std::from_chars(str.data(), 
                                     str.data() + str.size(), 
                                     value);

    if (res.ec == std::errc()) {
        std::cout << "value: " << value << ", distance: " << res.ptr - str.data() << '\n';
    }
    else if (res.ec == std::errc::invalid_argument) {
        std::cout << "invalid argument!\n";
    }
    else if (res.ec == std::errc::result_out_of_range) {
        std::cout << "out of range! res.ptr distance: " << res.ptr - str.data() << '\n';
    }
}
