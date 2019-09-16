// folds_print.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>

template<typename ...Args>
void FoldPrintBasic(Args&&... args) {
    (std::cout << ... << std::forward<Args>(args)) << '\n';
}

template<typename ...Args>
void FoldSeparateLine(Args&&... args) {
    auto separateLine = [](const auto& v) {
        std::cout << v << '\n';
    };
    (... , separateLine (std::forward<Args>(args))); // over comma operator
}

template<typename First, typename ...Args>
void FoldPrintComma(First&& f, Args&&... args) {
    std::cout << f;
    auto withComma = [](const auto& v) {
        std::cout << ", " << v;  
    };
    (... , withComma(std::forward<Args>(args)));
    std::cout << '\n';
}

template<typename T>
void linePrinterInfo(const T& x) {
    if constexpr (std::is_integral_v<T>)
        std::cout << "num: " << x << '\n';
    else if constexpr (std::is_floating_point_v<T>)
        std::cout << "flt: " << x << '\n';
    else if constexpr(std::is_pointer_v<T>) {
        std::cout << "ptr, ";
        linePrinterInfo(*x);
    }
    else
        std::cout << x << '\n'; 
}

template<typename ... Args>
void PrintWithInfo(Args ... args) {
    (linePrinterInfo(std::forward<Args>(args)), ...); // fold expression over the comma operator
}
 
int main() {
    std::cout << "-- basic: \n";
    FoldPrintBasic("hello", 10, 20, 30);
    
    std::cout << "-- lines: \n";
    FoldSeparateLine("hello", 10, 20, 30);
    
    std::cout << "-- comma: \n";
    FoldPrintComma("hello", 10, 20, 30);
    
    std::cout << "-- extra info: \n";
    int i = 10;
    PrintWithInfo(&i, std::string("hello"), 10, 20.5, 30);
}