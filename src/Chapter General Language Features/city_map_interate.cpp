// city_map_iterate.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <map>
#include <iostream>
#include <string>

int main() {
    const std::map<std::string, int> mapCityPopulation {
        { "Beijing", 21'707'000 },
        { "Tokyo", 9'273'000 },
        { "London", 8'787'892 },
        { "New York", 8'622'698 },
        { "Rio de Janeiro", 6'520'000 }
    };
    
    for (auto&[city, population] : mapCityPopulation)
        std::cout << city << ": " << population << '\n';
}