// optional_reset.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>
#include <iostream>
#include <string>

class UserName {
public:
    explicit UserName(std::string str) : mName(std::move(str)) { 
        std::cout << "UserName::UserName('" << mName << "')\n"; 
    }
    ~UserName() {
        std::cout << "UserName::~UserName('" << mName << "')\n"; 
    }
    UserName(const UserName& u) : mName(u.mName) {
        std::cout << "UserName::UserName(copy '" << mName << "')\n";
    }
    UserName(UserName&& u) : mName(std::move(u.mName)) {
        std::cout << "UserName::UserName(move '" << mName << "')\n";
    }
    UserName& operator=(const UserName& u) { // copy assignment  
        mName = u.mName;
        
        std::cout << "UserName::=(copy '" << mName << "')\n";
        
        return *this;
    }
    UserName& operator=(UserName&& u) { // move assignment
        mName = std::move(u.mName);
        
        std::cout << "UserName::=(move '" << mName << "')\n";
        
        return *this;
    }
    
private:
    std::string mName;
};

int main() {
    std::optional<UserName> oEmpty;
    
    // emplace:
    oEmpty.emplace("Steve");
    
    // calls ~Steve and creates new Mark:
    oEmpty.emplace("Mark");
    
    // reset so it's empty again
    oEmpty.reset(); // calls ~Mark
    // same as:
    //oEmpty = std::nullopt;
    
    // assign a new value:
    oEmpty.emplace("Fred");
    oEmpty = UserName("Joe");
}