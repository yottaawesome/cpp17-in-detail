// demo_map.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> mapUsersAge { { "Alex", 45 }, { "John", 25 } };
    
    std::map mapCopy{mapUsersAge};
    
    if (auto [iter, wasAdded] = mapCopy.insert_or_assign("John", 26); !wasAdded)
        std::cout << iter->first << " reassigned...\n";
        
    for (const auto& [key, value] : mapCopy)
        std::cout << key << ", " << value << '\n';
}