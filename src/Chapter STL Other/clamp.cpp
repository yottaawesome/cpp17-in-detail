// clamp.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <algorithm>  // clamp
 
int main() {
    std::cout << std::clamp(300, 0, 255) << '\n';   
    std::cout << std::clamp(-10, 0, 255) << '\n';    
}