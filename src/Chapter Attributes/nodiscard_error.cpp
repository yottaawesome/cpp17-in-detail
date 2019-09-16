// nodiscard_error.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string_view>

enum class [[nodiscard]] ErrorCode {
    OK,
    Fatal,
    System,
    FileIssue
};

ErrorCode OpenFile(std::string_view fileName) {
    return ErrorCode::OK; 
}

ErrorCode SendEmail(std::string_view sendto, std::string_view text) { 
    return ErrorCode::OK; 
}

ErrorCode SystemCall(std::string_view text) { 
    return ErrorCode::OK; 
}

int main() {
    if (OpenFile("Test.txt") == ErrorCode::OK) {
        if (SystemCall("Success!") != ErrorCode::OK)
            return 1;
    }
    
    return 0;
}