// inser_or_assign.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <map>
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

int main(){
    std::map<std::string, User> mapNicks;
    //mapNicks["John"] = User("John Doe"); // error: no default ctor for User()
    
    auto [iter, inserted] = mapNicks.insert_or_assign("John", User("John Doe"));
    if (inserted)
	    std::cout << iter->first <<" entry was inserted\n";
	else 
	    std::cout << iter->first << " entry was updated\n";
}