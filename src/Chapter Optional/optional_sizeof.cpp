// optional_sizeof.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <optional>

struct RangeOpt {
    std::optional<double> mMin;
    std::optional<double> mMax;
};

struct Range {
    bool mMinAvailable;
    bool mMaxAvailable;
    double mMin;
    double mMax;
};

int main() {
    return sizeof(RangeOpt);
}
