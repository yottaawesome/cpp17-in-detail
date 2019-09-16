// has_include.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2019

#include <iostream>
#include <optional>
#include <string>

#ifdef __has_include 
#  if __has_include(<charconv>)
#    define has_charconv 1
#    include <charconv>
#  endif
#endif

std::optional<int> ConvertToInt(const std::string& str) {
    int value { };
    #ifdef has_charconv
    const auto last = str.data() + str.size();
    const auto res = std::from_chars(str.data(), last, value);
    if (res.ec == std::errc{} && res.ptr == last)
        return value;
    #else
    try {
        size_t read = 0;
        value = std::stoi(str, &read);        
        if (str.size() == read)
            return value;
    }
    catch (...) { }
    #endif
    
    return std::nullopt;
}

int main() {
    #ifdef has_charconv
    std::cout << "has_charconv\n";
    #endif
    auto oint = ConvertToInt("Hello");
    std::cout << oint.has_value() << '\n';
    oint = ConvertToInt("10");
    std::cout << oint.has_value() << '\n';
}