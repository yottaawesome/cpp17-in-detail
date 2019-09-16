// avoiding_copies_string_view.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <string_view>

// we need to overload 'new' to see what's
// hapenning under the hood...
void* operator new(std::size_t n) {
    std::cout << "new " << n << " bytes\n";
    return malloc(n);
}

std::string StartFromWordStr(const std::string& str, const std::string& word) {
    return str.substr(str.find(word)); // substr creates a new string
}

std::string_view StartFromWord(std::string_view str, std::string_view word) {
    return str.substr(str.find(word)); // substr creates only a new view
}
 
int main() {
    // the original string, one allocation:
    std::string str {"Hello Amazing Programming Environment" };
    
    std::cout << "string version:\n";
    
    // one allocation to pass the param "Programming Environment"
    // another allocation in substr inside the function
    auto subStr = StartFromWordStr(str, "Programming Environment");
    std::cout << subStr << '\n';
    
    std::cout << "string_view version:\n";
    
    // no allocation for the sub range:
    auto subView = StartFromWord(str, "Programming Environment");
    std::cout << subView << '\n';
}