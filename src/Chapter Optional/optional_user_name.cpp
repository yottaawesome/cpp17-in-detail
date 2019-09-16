// optional_reset.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>
#include <iostream>

class UserRecord {
public:
    UserRecord (std::string name, std::optional<std::string> nick, std::optional<int> age)
    : mName{std::move(name)}, mNick{std::move(nick)}, mAge{age}
    {
    }

    friend std::ostream& operator << (std::ostream& stream, const UserRecord& user);

private:
    std::string mName;
    std::optional<std::string> mNick;
    std::optional<int> mAge;
};

std::ostream& operator << (std::ostream& os, const UserRecord& user) {
    os << user.mName;
    
    if (user.mNick)
        os << ' ' << *user.mNick;

    if (user.mAge)
        os << ' ' << "age of " << *user.mAge;
        
    return os;
}

int main() {
    UserRecord tim { "Tim", "SuperTim", 16 };
    UserRecord nano { "Nathan", std::nullopt, std::nullopt };
    
    std::cout << tim << '\n';
    std::cout << nano << '\n';
}