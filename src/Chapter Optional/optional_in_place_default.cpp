// optional_in_place_default.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>
#include <iostream>
#include <string>

void* operator new(std::size_t count) {
    std::cout << "allocating " << count << " bytes" << std::endl;
    return malloc(count);
}

void operator delete(void* ptr) noexcept {
    std::cout << "global op delete called\n";
    std::free(ptr);
}

class UserName {
public:
    explicit UserName() : mName("Default") { 
        std::cout << "UserName::UserName('";
        std::cout << mName << "')\n"; 
    }

    explicit UserName(const std::string& str) : mName(str) { 
        std::cout << "UserName::UserName('";
        std::cout << mName << "')\n"; 
    }
    ~UserName() {
        std::cout << "UserName::~UserName('";
        std::cout << mName << "')\n"; 
    }
    UserName(const UserName& u) : mName(u.mName) {
        std::cout << "UserName::UserName(copy '";
        std::cout << mName << "')\n";
    }
    UserName(UserName&& u) noexcept : mName(std::move(u.mName)) {
        std::cout << "UserName::UserName(move '";
        std::cout << mName << "')\n";
    }
    UserName& operator=(const UserName& u) { // copy assignment
        mName = u.mName;
        
        std::cout << "UserName::=(copy '";
        std::cout << mName << "')\n";
        
        return *this;
    }
    UserName& operator=(UserName&& u) noexcept { // move assignment
        mName = std::move(u.mName);
        
        std::cout << "UserName::=(move '";
        std::cout << mName << "')\n";
        
        return *this;
    }
    
private:
    std::string mName;
};

int main() {
    std::optional<UserName> opt(UserName{});
    //std::optional<UserName> opt{std::in_place};
}