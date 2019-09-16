// logical_metafunctions.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2019

#include <iostream>
#include <type_traits>

template<typename... Ts>
std::enable_if_t<std::conjunction_v<std::is_same<int, Ts>...> >
PrintIntegers(Ts ... args) { 
    (std::cout << ... << args) << '\n';
}

int main() {
    PrintIntegers(1, 2, 3, 4);
    
    // doesn't compile
    // PrintIntegers(1, 2, 3, 4.5f);
    
    return 0;
}