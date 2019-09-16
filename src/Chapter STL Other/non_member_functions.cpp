// non_member_functions.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <vector>

template <class Container>
void PrintBasicInfo(const Container& cont) {
    std::cout << typeid(cont).name() << '\n';
    std::cout << std::size(cont) << '\n';
    std::cout << std::empty(cont) << '\n';
    
    if (!std::empty(cont))
        std::cout << *std::data(cont) << '\n';
}

int main() {
    std::vector<int> iv { 1, 2, 3, 4, 5 };
    PrintBasicInfo(iv);
    float arr[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
    PrintBasicInfo(arr);
}