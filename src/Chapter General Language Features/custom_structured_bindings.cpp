// custom_structured_bindings.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <tuple>

class UserEntry {
public:
    UserEntry() { }
    
    void Load() { 
        // simulate loading from db...
        name="John"; 
        age=45;
        cacheEntry = 10;
    }
    
    std::string GetName() const { return name; }
    unsigned GetAge() const { return age; }
    
private:
    std::string name;
    unsigned age { 0 };
    size_t cacheEntry { 0 };
};

// read access:
template <size_t I> auto get(const UserEntry& u) {
    if constexpr (I == 0) return u.GetName();
    else if constexpr (I == 1) return u.GetAge();
}

namespace std {
    template <> struct tuple_size<UserEntry> : std::integral_constant<size_t, 2> { };

    template <> struct tuple_element<0,UserEntry> { using type = std::string; };
    template <> struct tuple_element<1,UserEntry> { using type = unsigned; };
}

int main () {
    UserEntry u;
    u.Load();
    auto [name, age] = u;
    std:: cout << name << ", " << age << '\n';
}