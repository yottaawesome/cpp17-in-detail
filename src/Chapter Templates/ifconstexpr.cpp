// ifconstexpr.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <memory>

template <typename Concrete, typename... Ts>
std::unique_ptr<Concrete> constructArgs(Ts&&... params) { 
    
// replace this with "if constexpr" to make it compile    
  if (std::is_constructible_v<Concrete, Ts...>)
      return std::make_unique<Concrete>(std::forward<Ts>(params)...);
   else
       return nullptr;
}

class Test {
public:
    explicit Test(int, int) { }
};
 
int main() {
    auto p = constructArgs<Test>(10, 10, 10);
}