// par_exceptions.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

int main() {
    // if you throw exception from the lambda
    // then the std::Terminate will be called
    // exceptions are not re thrown
    try {
        std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        std::for_each(std::execution::par, v.begin(), v.end(), 
            [](int& i) {
			
			++i;

            if (i == 5)
                throw std::runtime_error("something wrong... !");
        });
    }
    catch (const std::bad_alloc& e){
        std::cout << "Error in execution: " << e.what() << '\n';
    }
    catch (const std::exception& e) { // will not happen
        std::cout << e.what() << '\n'; 
    }
    catch (...) {
        std::cout << "error!\n";
    }

    return 0;
}

