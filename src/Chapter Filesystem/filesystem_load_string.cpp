// filesystem_list_files.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <chrono>
#include <filesystem>  
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

[[nodiscard]] std::string GetFileContents(const fs::path& filePath) {
    std::ifstream inFile{ filePath, std::ios::in | std::ios::binary };
    if (!inFile)
        throw std::runtime_error("Cannot open " + filePath.filename().string());
    
    const auto fsize = fs::file_size(filePath);
    if (fsize > std::numeric_limits<size_t>::max())
        throw std::runtime_error("file is too large to fit into size_t! " + filePath.filename().string()); 

    std::string str(static_cast<size_t>(fsize), 0);

    inFile.read(str.data(), str.size());
    if (!inFile)
        throw std::runtime_error("Could not read the full contents from " + filePath.filename().string());

    return str;
}

int main(int argc, char* argv[]) {
    if (argc <= 1)
        return 0;

    try {
        const auto str = GetFileContents(argv[1]);
        std::cout << "string size: " << str.size() << '\n';
    }
    catch (const fs::filesystem_error& err) {
        std::cerr << "filesystem error! " << err.what() << '\n';
        if (!err.path1().empty())
            std::cerr << "path1: " << err.path1().string() << '\n';
        if (!err.path2().empty())
            std::cerr << "path2: " << err.path2().string() << '\n';
    }
    catch (const std::exception& ex) {
        std::cerr << "general exception: " << ex.what() << '\n';
    }
    catch (...) {
        std::cerr << "unknown exception!\n";
    }
}