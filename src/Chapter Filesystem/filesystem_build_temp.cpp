// filesystem_build_temp.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <chrono>
#include <filesystem>  
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>  
#include <string>  

namespace fs = std::filesystem;

std::vector<fs::path> GeneratePathNames(const fs::path& tempPath, unsigned num) {
    std::vector<fs::path> outPaths{ num, tempPath };
    for (auto& dirName : outPaths) {
        const auto addr = reinterpret_cast<uintptr_t>(&dirName);
        dirName /= std::string("tt") + std::to_string(addr);
    }
    return outPaths;
}

void CreateTempFiles(const fs::path& dir, unsigned numFiles) {
    auto files = GeneratePathNames(dir, numFiles);
    for (auto &oneFile : files) {
        std::ofstream entry(oneFile.replace_extension("txt"));
        entry << "Hello World";
    }
}

void CreateTempData(const fs::path& tempPath, unsigned numDirectories, unsigned numFiles) {
    fs::create_directory(tempPath);
    auto dirPaths = GeneratePathNames(tempPath, numDirectories);

    for (auto& dir : dirPaths) {
        if (fs::create_directory(dir))
            CreateTempFiles(dir, numFiles);
    }
}

int main(int argc, char* argv[]) {
    try {
        const fs::path startingPath{ argc >= 2 ? argv[1] : fs::current_path() };
        const std::string strTempName{ argc >= 3 ? argv[2] : "temp" };
        const int numDirectories{ argc >= 4 ? std::stoi(argv[3]) : 4 };
        const int numFiles{ argc >= 5 ? std::stoi(argv[4]) : 4 };

        if (numDirectories < 0 || numFiles < 0)
            throw std::runtime_error("negative input numbers...");

        const fs::path tempPath = startingPath / strTempName;
        CreateTempData(tempPath, numDirectories, numFiles);
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
}