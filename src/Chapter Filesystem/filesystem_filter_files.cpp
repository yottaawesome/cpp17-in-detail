// filesystem_filter_files.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <algorithm>
#include <chrono>
#include <filesystem>  
#include <iostream>
#include <regex>

namespace fs = std::filesystem;

struct FileEntry {
    fs::path mPath;
    uintmax_t mSize{ 0 };

    static FileEntry CreateFromPath(const fs::path& filePath) {
        return FileEntry{ filePath, fs::file_size(filePath) };
    }

    friend bool operator < (const FileEntry& a, const FileEntry& b) noexcept {
        return a.mSize < b.mSize;
    }
};

std::vector<FileEntry> CollectFiles(const fs::path& inPath) {
    std::vector<fs::path> paths;
    if (fs::exists(inPath) && fs::is_directory(inPath)) {		
        std::filesystem::recursive_directory_iterator dirpos{ inPath };

        std::copy_if(begin(dirpos), end(dirpos), std::back_inserter(paths),
            [](const fs::directory_entry& entry) {
                return entry.is_regular_file();
            }
        );
    }
    std::vector<FileEntry> files(paths.size());
    std::transform(paths.cbegin(), paths.cend(), files.begin(), FileEntry::CreateFromPath);
    return files;
}

std::vector<FileEntry> CollectFilesOpt(const fs::path& inPath) {
    std::vector<FileEntry> files;
    if (fs::exists(inPath) && fs::is_directory(inPath)) {
        for (const auto& entry : fs::recursive_directory_iterator{ inPath }) {
            if (entry.is_regular_file())
                files.push_back({ entry, entry.file_size() });
        }
    }
    return files;
}

int main(int argc, char* argv[]) {
    try {
        const fs::path pathToShow{ argc >= 2 ? argv[1] : fs::current_path() };
        const std::regex reg(argc >= 3 ? argv[2] : "");

        auto files = CollectFiles(pathToShow);

        std::sort(files.begin(), files.end());

        for (auto& entry : files) {
            const auto strFileName = entry.mPath.filename().string();
            if (std::regex_match(strFileName, reg))
                std::cout << strFileName << "\tsize: " << entry.mSize << '\n';
        }
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