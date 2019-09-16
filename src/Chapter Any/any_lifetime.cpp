// any_lifetime.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <any>
 
void* operator new(std::size_t count) {
    std::cout << "allocating: " << count << " bytes" << std::endl;
    return malloc(count);
} 
 
void operator delete(void* ptr) noexcept {
    std::puts("global op delete called");
    std::free(ptr);
} 
 
class MyType {
public:
    MyType() { std::cout << "MyType::MyType\n"; }
    ~MyType() { std::cout << "MyType::~MyType\n"; }
};
 
int main() {
    std::any a;
    a.emplace<std::string>("Hello super");
    a = 16;
    std::cout << std::any_cast<int>(a) << '\n';
    a.emplace<MyType>();
    a = 16;
    std::cout << std::any_cast<int>(a) << '\n';
    
    {
        std::any var = std::make_any<MyType>();
        var = 100.0f;
        std::cout << std::any_cast<float>(var) << '\n';
    }
}