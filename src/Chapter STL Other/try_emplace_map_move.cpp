// try_emplace_map_move.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <string>
#include <map>

int main() {
    std::map<std::string, std::string> m;
    m["Hello"] = "World";
    
    std::string s = "C++";
    m.emplace(std::make_pair("Hello", std::move(s)));
    
    // what happens with the string 's'?
    std::cout << s << '\n';
    std::cout << m["Hello"] << '\n';
    
    s = "C++";
    m.try_emplace("Hello", std::move(s));
    std::cout << s << '\n';
    std::cout << m["Hello"] << '\n';
}