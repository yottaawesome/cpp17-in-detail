// filesystem_list_files.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <chrono>
#include <filesystem>  
#include <iostream>

namespace fs = std::filesystem;

void DisplayDirectoryTree(const fs::path& pathToShow, int level = 0) {
    if (!fs::exists(pathToShow) || !fs::is_directory(pathToShow))
        return;

    const auto lead = std::wstring(level * 3, L' ');
    for (const auto& entry : fs::directory_iterator(pathToShow)) {
        auto filenameStr = entry.path().filename().wstring();
        if (fs::is_directory(entry)) {
            std::wcout << lead << filenameStr << L'\n';
            DisplayDirectoryTree(entry, level + 1);
        }
        else if (fs::is_regular_file(entry)) {
            std::wcout << lead << filenameStr
                << L", size " << fs::file_size(entry) << L" bytes\n";
        }
        else
            std::wcout << lead << L" [?]" << filenameStr << L'\n';
    }
}

int main(int argc, char* argv[]) {
    try {
        const fs::path pathToShow{ argc >= 2 ? argv[1] : fs::current_path() };

        std::wcout << L"listing files in the directory: " 
                  << fs::absolute(pathToShow).wstring() << L'\n';
        std::wcout << L"current path is: " << fs::current_path().wstring() << L'\n';

        DisplayDirectoryTree(pathToShow);
    }
    catch (const fs::filesystem_error& err) {
        std::cerr << "filesystem error! " << err.what() << '\n';
    }
    catch (const std::exception& ex) {
        std::cerr << "general exception: " << ex.what() << '\n';
    }
    catch (...) {
        std::cerr << "unknown exception!\n";
    }
}