// shuffle.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main() {
    std::vector<int> vec = { 0, 1, 2, 3, 4, 5 };
    
    // Pre-C++17:
    std::random_shuffle(begin(vec), end(vec));
    
    for (auto& elem : vec) 
        std::cout << elem << ", ";
        
    // C++17 version:
    std::random_device randDev;
    std::mt19937 gen(randDev());
 
    std::shuffle(begin(vec), end(vec), gen);
    
    for (auto& elem : vec) 
        std::cout << elem << ", ";
}