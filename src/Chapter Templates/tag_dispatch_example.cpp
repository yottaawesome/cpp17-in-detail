// tag_dispatching_example.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2019

#include <iostream>
#include <type_traits>

// Tag dispatching
template <typename T>
T simpleTypeInfoTagImpl(T t, std::true_type) {
    std::cout << "foo<integral T> " << t << '\n';
    return t;
}

template <typename T>
T simpleTypeInfoTagImpl(T t, std::false_type) {
    std::cout << "not integral \n";
    return t;
}

template <typename T>
T simpleTypeInfoTag(T t) {
    return simpleTypeInfoTagImpl(t, std::is_integral<T>{});
}

int main() {
    simpleTypeInfoTag(10);
    simpleTypeInfoTag(10.5f);
    
    return 0;
}