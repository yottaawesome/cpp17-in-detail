// func_except_type.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

using TNoexceptVoidFunc = void (*)() noexcept;
void SimpleNoexceptCall(TNoexceptVoidFunc f) {
    f();
}

using TVoidFunc = void (*)();
void SimpleCall(TVoidFunc f) {
    f();
}

void fNoexcept() noexcept { }
void fRegular() { }

int main() {
    SimpleNoexceptCall(fNoexcept);
    //SimpleNoexceptCall(fRegular); // cannot convert
    
    SimpleCall(fNoexcept); // converts to regular function
    SimpleCall(fRegular);
}