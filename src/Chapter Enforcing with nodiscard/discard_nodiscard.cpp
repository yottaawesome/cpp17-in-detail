// discard_nodiscard.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

[[nodiscard]] int Compute() { return 42; }

template <class T> inline void discard_on_purpose(T&&) { }

int main()
{
    // with an attribute:
    [[maybe_unused]] auto t = Compute();
    
    // separate function:
    discard_on_purpose(Compute());
    
    // casting to void:
    static_cast<void>(Compute());
    return 0;
}