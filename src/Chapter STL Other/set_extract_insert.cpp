// set_extract_insert.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <set>
#include <string>
#include <iostream>

struct User {
    std::string name;
    
    User(std::string s) : name(std::move(s)) {
        std::cout << "User::User(" << name << ")\n";
    }
    ~User() {
        std::cout << "User::~User(" << name << ")\n";
    }
    User(const User& u) : name(u.name) { 
        std::cout << "User::User(copy, " << name << ")\n";
    }
    
    friend bool operator<(const User& u1, const User& u2) {
        return u1.name < u2.name;
    }
};

int main() {
    std::set<User> setNames;
    setNames.emplace("John");
    setNames.emplace("Alex");
    setNames.emplace("Bartek");
    std::set<User> outSet;
    
    std::cout << "move John...\n";
    // move John to the outSet
    auto handle = setNames.extract(User("John"));
    outSet.insert(std::move(handle));
    
    for (auto& elem : setNames)
        std::cout << elem.name << '\n';
        
    std::cout << "cleanup...\n";
}