// optional_return.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

std::vector<int> CreateVec() {
    std::vector<int> v { 0, 1, 2, 3, 4 };
    std::cout << std::hex << v.data() << '\n';
    //return {std::move(v)}; // this one will cause a copy
    return (v); // this one moves
    //return v; // this one moves as well
}

std::optional<std::vector<int>> CreateOptVec() {
    std::vector<int> v { 0, 1, 2, 3, 4 };
    std::cout << std::hex << v.data() << '\n';
    return {v}; // this one will cause a copy
    //return v; // this one moves
}

std::optional<std::string> CreateOptStr(){
    std::string s { "Hello Super Long String" }; // prevent SSO
    std::cout << std::hex << static_cast<void *>(s.data()) << '\n';
    //return {s}; // this one will cause a copy
    return s; // this one moves
}

std::unique_ptr<int> CreatePtr() { 
    std::unique_ptr<int> p; 
    //return {p};  // uses copy of unique_ptr and so it breaks...
    return p; // this one moves, so it's fine with unique_ptr
}

int main() {
    std::cout << "CreateVec:\n";
    auto v1 = CreateVec();
    std::cout << std::hex << v1.data() << '\n';
    
    std::cout << "CreateOptVec:\n";
    auto v = CreateOptVec();
    std::cout << std::hex << v->data() << '\n';
    
    std::cout << "CreateOptStr:\n";
    auto s = CreateOptStr();
    std::cout << std::hex << static_cast<void *>(s->data()) << '\n';
    
    auto p = CreatePtr();
}