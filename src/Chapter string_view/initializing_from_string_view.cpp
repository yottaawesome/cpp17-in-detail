// initializing_from_string_view.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string_view>
#include <iostream>
#include <string>

using namespace std::literals;

// we need to overload 'new' to see what's
// hapenning under the hood...
void* operator new(std::size_t n) {
    std::cout << "new " << n << " bytes\n";
    return malloc(n);
}

class UserName {
std::string mName;

public:
    //UserName(std::string str) : mName(std::move(str)) { }
    UserName(const std::string& str) : mName(str) { }
    //UserName(std::string_view sv) : mName(sv) { }
   
};

int main() {
    UserName u1{"John With Very Long Name"};

    std::string s { "Marc With Very Long Name"};
    UserName u2 { std::move(s) };
}