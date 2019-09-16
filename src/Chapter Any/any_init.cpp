// any_demo.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <any>
#include <map>
 
void* operator new(std::size_t count) {
    std::cout << " allocating: " << count << " bytes" << std::endl;
    return malloc(count);
} 
 
void operator delete(void* ptr) noexcept {
    std::puts("global op delete called");
    std::free(ptr);
} 
 
int main() {
    auto a = std::any(12);
    
    // set any value:
    a = std::string("Hello!");
    a = 16;
    // reading a value:
    
    // we can read it as int
    std::cout << std::any_cast<int>(a) << '\n'; 
 
    // but not as string:
    try {
        std::cout << std::any_cast<std::string>(a) << '\n';
    }
    catch(const std::bad_any_cast& e) {
        std::cout << e.what() << '\n';
    }
    
    // reset and check if it contains any value:
    a.reset();
    if (!a.has_value())
        std::cout << "a is empty!" << '\n';
    
    // you can use it in a container:
    std::map<std::string, std::any> m;
    m["integer"] = 10;
    m["string"] = std::string("Hello World");
    m["float"] = 1.0f;
    
    for (auto &[key, val] : m) {
        if (val.type() == typeid(int))
            std::cout << "int: " << std::any_cast<int>(val) << '\n';
        else if (val.type() == typeid(std::string))
            std::cout << "string: " << std::any_cast<std::string>(val) << '\n';
        else if (val.type() == typeid(float))
            std::cout << "float: " << std::any_cast<float>(val) << '\n';
    }
}