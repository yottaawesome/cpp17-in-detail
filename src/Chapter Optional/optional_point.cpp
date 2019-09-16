// optional_point.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>

struct Point {
    Point(int a, int b) : x(a), y(b) { }

    int x;
    int y;
};

int main() {
    std::optional<Point> opt{std::in_place, 0, 1};
    std::optional<Point> opt2{{0, 1}};

    return sizeof(Point);
}