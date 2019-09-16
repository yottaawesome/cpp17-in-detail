// Chapter Variant/variant_visit_multiple.cpp
#include <iostream>
#include <variant>

template<class... Ts> 
struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct Pizza { };
struct Chocolate { };
struct Salami { };
struct IceCream { };

int main() {
    std::variant<Pizza, Chocolate, Salami, IceCream> firstIngredient { IceCream() };
    std::variant<Pizza, Chocolate, Salami, IceCream> secondIngredient { Chocolate()};
    
    std::visit(overloaded{
        [](const Pizza& p, const Salami& s) {
                std::cout << "here you have, Pizza with Salami!\n";
            },
        [](const Salami& s, const Pizza& p) {
                std::cout << "here you have, Pizza with Salami!\n";
            },
        [](const Chocolate& c, const IceCream& i) {
                std::cout << "Chocolate IceCream!\n";
            },
        [](const IceCream& i, const Chocolate& c) {
                std::cout << "Chocolate IceCream!\n";
            },
        [](auto a, auto b) {
                std::cout << "invalid composition...\n";
            },
    }, firstIngredient, secondIngredient);
    
    return 0;
}