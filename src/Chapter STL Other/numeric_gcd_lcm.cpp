// numeric_gcd_lcm.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <numeric>  // for gcm, lcm
 
int main() {
    std::cout << std::gcd(24, 60) << '\n';
    std::cout << std::lcm(15, 50) << '\n';     
}