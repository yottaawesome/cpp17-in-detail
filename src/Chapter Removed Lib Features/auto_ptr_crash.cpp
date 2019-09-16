// auto_ptr_crash.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

// don't compile with C++17 std flag!

#include <iostream>
#include <memory>

void doSomething(std::auto_ptr<int> myPtr) {
    *myPtr = 11;
}

void AutoPtrTest() {
    std::auto_ptr<int> myTest(new int(10));
    doSomething(myTest);
    *myTest = 12;
}

int main() {
    AutoPtrTest();
}