// any_changing.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <any>
#include <cassert> 
#include <vector>

class MyType {
    int a, b;
    
public:
    MyType(int x, int y) : a(x), b(y) { }
};
 
int main() {
    // default initialization:
    std::any a;
    assert(!a.has_value());
    
    a = MyType(10, 11);
    a = std::string("Hello");
    
    a.emplace<float>(100.5f);
    a.emplace<std::vector<int>>({10, 11, 12, 13});
    a.emplace<MyType>(10, 11);
}