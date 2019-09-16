// string_view_null.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>
#include <iostream>
#include <string>
#include <string_view>
#include <stdio.h>
#include <charconv>

// API that only uses null-terminated strings
void ConvertAndShow(const char *str) {
    auto f = atof(str);
    std::cout << f << '\n';
}

int main() {
    std::string s = "Hello World";
    std::cout << s.size() << '\n';
    std::string_view sv = s;
    auto sv2 = sv.substr(0, 5);
    std::cout << sv2.data() << '\n'; // oops!
    
    // printf issues:
    printf("%s\n", sv2.data());
    printf("%.*s\n", static_cast<int>(sv2.size()), sv2.data());
    
    // conversions, like atof, atoi:
    {
        std::string number = "123.456";
        std::string_view svNum { number.data(), 3 };
        auto f = atof(svNum.data()); // should be 123, but is 123.456!
        std::cout << f << '\n';
    
        // use from_chars (C++17)
        int res = 0;
        std::from_chars(svNum.data(), svNum.data()+svNum.size(), res);
        std::cout << res << '\n';
    }
    
    {
        std::string number = "123.456";
        std::string_view svNum { number.data(), 3 };
        // ... some code
        std::string tempStr { svNum.data(), svNum.size() };
        ConvertAndShow(tempStr.c_str());
    }
}