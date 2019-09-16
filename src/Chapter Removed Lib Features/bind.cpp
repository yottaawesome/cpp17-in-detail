// bind.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <functional>
#include <iostream>

int main() {
    auto onePlus = std::bind1st(std::plus<int>(), 1);
    std::cout << onePlus(10) << ',';
    auto minusOne = std::bind2nd(std::minus<int>(), 1);
    std::cout << minusOne(10) << '\n';
    
    // with hardcoded lambdas:
    auto lamOnePlus1 = [](int b) { return 1 + b; };
    std::cout << lamOnePlus1(10) << ',';
    auto lamMinusOne1 = [](int b) { return b - 1; };
    std::cout << lamMinusOne1(10) << '\n';
    
    // a capture with an initializer
    auto lamOnePlus = [a=1](int b) { return a + b; };
    std::cout << lamOnePlus(10) << ',';
    auto lamMinusOne = [a=1](int b) { return b - a; };
    std::cout << lamMinusOne(10) << '\n';
    
    // with bind:
    using namespace std::placeholders; 
    auto onePlusBind = std::bind(std::plus<int>(), 1, _1);
    std::cout << onePlusBind(10) << ',';
    auto minusOneBind = std::bind(std::minus<int>(), _1, 1);
    std::cout << minusOneBind(10) << '\n';
}