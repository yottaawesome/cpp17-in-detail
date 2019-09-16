// capture_this.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2019

#include <iostream>
#include <string>

struct Test  {
    void foo() {
        std::cout << "before: " << m_str  << '\n';
        auto addWordLambda = [this]()  { m_str += "World"; };
        addWordLambda ();
        std::cout << "after: " << m_str  << '\n';
    }
    
    void fooCopy() {
        std::cout << "before: " << m_str  << '\n';
        auto addWordLambda = [*this]() mutable { m_str += "World"; };
        addWordLambda();
        std::cout << "after: " << m_str  << '\n';
    }
    
    std::string m_str {"Hello "};
};

int main() {
    Test test;
    test.foo();
    
    Test copyTest;
    copyTest.fooCopy();
    
    return 0;
}