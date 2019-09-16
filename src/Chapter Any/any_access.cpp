// any_access.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <any>
#include <cassert> 
#include <vector>

struct MyType
{
    int a, b;
    
    MyType(int x, int y) : a(x), b(y) { }
    
    void Print() { std::cout << a << ", " << b << '\n'; }
};
 
int main()
{
    std::any var = std::make_any<MyType>(10, 10);
    try
    {
        std::any_cast<MyType&>(var).Print();
        std::any_cast<MyType&>(var).a = 11; // read/write
        std::any_cast<MyType&>(var).Print();
        std::any_cast<int>(var); // throw!
    }
    catch(const std::bad_any_cast& e) 
    {
        std::cout << e.what() << '\n';
    }
    
    int* p = std::any_cast<int>(&var);
    std::cout << (p ? "contains int... \n" : "doesn't contain an int...\n");
    
    if (MyType* pt = std::any_cast<MyType>(&var); pt)
    {
        pt->a = 12;
        std::any_cast<MyType&>(var).Print();
    }
}