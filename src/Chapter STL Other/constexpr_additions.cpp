// constexpr_additions.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <array>

template<typename Range, typename Func, typename T>
constexpr T SimpleAccumulate(const Range& range, Func func, T init) {
    for (auto &&obj : range) { // begin/end are constexpr
        init += func(obj);
    }
    return init;
}

constexpr int square(int i) { return i*i; }

int main() {
    constexpr std::array arr{ 1, 2, 3 }; // clas deduction...
    
    // with constexpr lambda
    static_assert(SimpleAccumulate(arr, [](int i) constexpr { 
            return i * i; 
        }, 0) == 14);
        
    // with constexpr function
    static_assert(SimpleAccumulate(arr, &square, 0) == 14);
    
    return arr[0];
}