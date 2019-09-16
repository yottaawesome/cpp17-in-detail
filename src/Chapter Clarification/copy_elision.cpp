// copy_elision.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

// compile with -fno-elide-constructors on gcc to avoid elision in C++14
// g++ CopyElision.cpp -std=c++14 -fno-elide-constructors

#include <iostream>

struct Test {
    Test() { std::cout << "Test::Test\n"; }
    Test(const Test&) { std::cout << "Test(const Test&)\n"; }
    Test(Test&&) { std::cout << "Test(Test&&)\n"; }
    ~Test() { std::cout << "~Test\n"; }
};

Test Create() {
    return Test();
}

int main() {
    auto n = Create();
}