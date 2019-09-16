// attributes.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

[[deprecated("use AwesomeFunc instead")]] void GoodFunc() { }

enum class ColorModes {
    RGB [[deprecated("use RGB8")]], // C++17 feature, that we can apply it on enumerations
    RGBA [[deprecated("use RGBA8")]],
    RGBA16F,
    RGB8,
    RGBA8
};

int main() {
	GoodFunc();
    
    auto c = ColorModes::RGBA;
    c = ColorModes::RGB;
}