// variant_valueless.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <variant>
#include <map>
#include <charconv>
#include <cstring>

class ThrowingClass {
public:
    explicit ThrowingClass(int i) { if (i == 0) throw int (10); }
    operator int () { throw int(10); }
};


int main(int argc, char** argv) {
    std::variant<int, ThrowingClass> v;
    
    // change the value:
    try {
        v = ThrowingClass(0);
    }
    catch (...) {
        std::cout << "catch(...)\n";
        // we keep the old state!
        std::cout << v.valueless_by_exception() << '\n';   
        std::cout << std::get<int>(v) << '\n'; 
    }
    
    // inside emplace
    try {
        v.emplace<0>(ThrowingClass(10)); // calls the operator int
    }
    catch (...) {
        std::cout << "catch(...)\n";
        // the old state was destroyed, so we're not in invalid state!
        std::cout << v.valueless_by_exception() << '\n';   
    }
    
    return 0;
}