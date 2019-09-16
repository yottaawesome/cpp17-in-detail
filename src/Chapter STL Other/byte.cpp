// byte.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <cstddef>

int main() {
    constexpr std::byte b{1};
    // std::byte c{3535353}; // error: narrowing conversion from int to unsigned_char
    
    constexpr std::byte c{255};
    
    // shifts:
    constexpr auto b1 = b << 7;
    static_assert(std::to_integer<int>(b)  == 0x01);
    static_assert(std::to_integer<int>(b1) == 0x80);
    
    // various bit operators, like &, |, &, etc
    constexpr auto c1 = b1 ^ c;
    static_assert(std::to_integer<int>(c)  == 0xff);
    static_assert(std::to_integer<int>(c1) == 0x7f);
    
    constexpr auto c2 = ~c1;
    static_assert(std::to_integer<int>(c2)  == 0x80);
    static_assert(c2 == b1);
}