// filesystem_permissions.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2019

#include <filesystem>  
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

std::ostream& operator<< (std::ostream& stream, fs::perms p) {
    stream << "owner: "
       << ((p & fs::perms::owner_read)  != fs::perms::none ? "r" : "-")
       << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
       << ((p & fs::perms::owner_exec)  != fs::perms::none ? "x" : "-");
    stream << " group: "
       << ((p & fs::perms::group_read)  != fs::perms::none ? "r" : "-")
       << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
       << ((p & fs::perms::group_exec)  != fs::perms::none ? "x" : "-");
    stream << " others: "
       << ((p & fs::perms::others_read)  != fs::perms::none ? "r" : "-")
       << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
       << ((p & fs::perms::others_exec)  != fs::perms::none ? "x" : "-");
    return stream;
}

int main(int argc, char* argv[]) {
    const std::string sTempName { "hello.txt" };
    {
        std::ofstream sample(sTempName);
        sample << "Hello World!\n";
    }
    
    try {
        std::cout << "after creation: " << fs::status(sTempName).permissions() << '\n';
        fs::permissions(sTempName, fs::perms::owner_read, fs::perm_options::remove);
        std::cout << "after change: " << fs::status(sTempName).permissions() << '\n';
        
        if (fs::remove(sTempName))
            std::cout << "temp file removed...\n";
    }
    catch (const fs::filesystem_error& err) {
        std::cerr << "filesystem error! " << err.what() << '\n';
    }
    catch (const std::exception& ex) {
        std::cerr << "general exception: " << ex.what() << '\n';
    }
    catch (...) {
        std::cerr << "general exception!\n";
    }
}