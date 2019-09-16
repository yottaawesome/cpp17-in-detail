// nodiscard_factory.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>

class Foo {
public:
    Foo(std::string param1, std::string param2) { }
    
    void Run() { }
};

[[nodiscard]] Foo BuildFoo() {
    std::string param1;
    std::string param2;
    return Foo(param1, param2);
}

int main() {
    auto foo = BuildFoo();
    foo.Run();
    
    return 0;
}