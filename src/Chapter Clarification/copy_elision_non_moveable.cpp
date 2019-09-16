// copy_elision_non_moveable.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <array>

// based on P0135R0
struct NonMoveable {
    NonMoveable(int x) : v(x) { }
    NonMoveable(const NonMoveable&) = delete;
    NonMoveable(NonMoveable&&) = delete;
  
    std::array<int, 1024> arr;
    int v;
};

NonMoveable make(int val) {
    if (val > 0)
        return NonMoveable(val);
  
    return NonMoveable(-val);
}

int main() {
    auto largeNonMoveableObj = make(90); // construct the object
    return largeNonMoveableObj.v;
}