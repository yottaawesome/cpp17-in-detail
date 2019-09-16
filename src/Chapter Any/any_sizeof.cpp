// any_sizeof.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <any>
#include <map>
 
void* operator new(std::size_t count) {
    std::cout << " allocating: " << count << " bytes" << std::endl;
    return malloc(count);
} 
 
void operator delete(void* ptr) noexcept {
    std::puts("global op delete called");
    std::free(ptr);
} 
 
template <int Num>
class Container {
    int _array[Num];      
};
 
int main() {
    std::cout << "sizeof(any): " << sizeof(std::any) << '\n';
    {
        std::cout << sizeof(Container<2>) << '\n';
        std::any t(Container<2>{});
    }
    {
        std::cout << sizeof(Container<3>) << '\n';
        std::any t(Container<3>{});
    }
}