// string_view_creation.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <string>
#include <string_view>

int main() {
    const char* cstr = "Hello World";
    
    // the whole string:
    std::string_view sv1 { cstr };
    std::cout << sv1 << ", len: " << sv1.size() << '\n';
    
    // slice
    std::string_view sv2 { cstr, 5 }; // not null-terminated!
    std::cout << sv2 << ", len: " << sv2.size() << '\n';
    
    // from string:
    std::string str = "Hello String";
    std::string_view sv3 = str;
    std::cout << sv3 << ", len: " << sv3.size() << '\n';
    
    // ""sv literal
    using namespace std::literals;
    std::string_view sv4 = "Hello\0 Super World"sv;
    std::cout << sv4 << ", len: " << sv4.size() << '\n';
    std::cout << sv4.data() << " - till zero\n";
}