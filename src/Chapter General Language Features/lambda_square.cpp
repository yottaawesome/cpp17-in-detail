// lambda_square.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2019

int main () {
    constexpr auto SquareLambda = [] (int n) { return n*n; };
    static_assert(SquareLambda(3) == 9, "");
}