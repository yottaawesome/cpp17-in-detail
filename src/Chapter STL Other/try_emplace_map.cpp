// try_emplace_map.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <string>
#include <map>

int main() {
    std::map<std::string, int> m;
    
    m["hello"] = 1;
    m["world"] = 2;
    
    // C++11 way:
    if (m.find("great") == std::end(m))
        m["great"] = 3;
    
    // the lookup is performed twice if "great" is not in the map
    
    // C++17 way:
    m.try_emplace("super", 4);
    m.try_emplace("hello", 5); // won't work, as it's already in the map

    for (const auto& [key, value] : m)
        std::cout << key << " -> " << value << '\n';
}