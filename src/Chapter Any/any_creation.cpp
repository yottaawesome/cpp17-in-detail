// any_creation.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <any>
#include <cassert> 

class MyType {
    int a, b;
    
public:
    MyType(int x, int y) : a(x), b(y) { }
};
 
int main() {
    // default initialization:
    std::any a;
    assert(!a.has_value());
    
	// initialization with an object:
	std::any a2{10}; // int
	std::any a3{MyType{10, 11}};

	// in_place:
	std::any a4{std::in_place_type<MyType>, 10, 11};
	std::any a5{std::in_place_type<std::string>, "Hello World"};

	// make_any
	std::any a6 = std::make_any<std::string>{"Hello World"};
}