// variant_polymorphism.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <variant>
#include <cassert>
#include <vector>

class Triangle {
public:
    void Render()  { std::cout << "Drawing a triangle!\n"; }
};

class Polygon {
public:
    void Render() { std::cout << "Drawing a polygon!\n"; }
};

class Sphere {
public:
    void Render() { std::cout << "Drawing a sphere!\n"; }
};

int main() {
    std::vector<std::variant<Triangle, Polygon, Sphere>> objects { 
        Polygon(), 
        Triangle(),
        Sphere(),
        Triangle()
    };
    
    auto CallRender = [](auto& obj) { obj.Render(); };
    
    for (auto& obj : objects)
        std::visit(CallRender, obj);
    
}