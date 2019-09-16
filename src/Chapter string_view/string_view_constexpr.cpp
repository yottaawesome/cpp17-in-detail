// string_view_constexpr.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

// compile with -O2 on GCC to get the following asm:
//
// main:
//     movl    $17, %eax
//     ret

#include <string_view>

int main() {
    using namespace std::literals;

    constexpr auto strv = "Hello Programming World"sv;
    constexpr auto strvCut = strv.substr("Hello "sv.size());
    
    static_assert(strvCut == "Programming World"sv);
    return strvCut.size();
}

