// filesystem_list_files.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <chrono>
#include <filesystem>  
#include <iostream>
#include <iomanip>
#include <optional>
#include <sstream>  
#include <string>  
#ifdef _MSC_VER
#define NOMINMAX
#include <windows.h>
#endif

namespace fs = std::filesystem;

std::optional<std::uintmax_t> ComputeFileSize(const fs::path& pathToCheck) {
    if (fs::exists(pathToCheck) && fs::is_regular_file(pathToCheck)) {
        auto err = std::error_code{};
        const auto filesize = fs::file_size(pathToCheck, err);
        if (err == std::error_code{} && filesize != static_cast<uintmax_t>(-1))
            return filesize;
    }

    return std::nullopt;
}

template <typename UnitStr, typename ... UnitsStr>
std::string UnitString(double value, double, UnitStr str) {
    return std::to_string(value) + ' ' + str;
}

template <typename UnitStr, typename ... UnitsStr>
std::string UnitString(double value, double unitStep, UnitStr str, UnitsStr ... strs) {
    if (value > unitStep)
        return UnitString(value / unitStep, unitStep, strs...);
    else
        return UnitString(value, unitStep, str);
}

std::string SizeToString(std::optional<std::uintmax_t> fsize) {
    if (fsize)
        return UnitString(static_cast<double>(*fsize), 1024, "B", "KB", "MB", "GB");

    return "err";
}

template <typename TDuration>
std::string ElapsedToString(const TDuration& dur) {
    const auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
    return UnitString(static_cast<double>(elapsed), 60.0, "seconds", "minutes", "hours");
}

std::string FileTimeToDate(fs::file_time_type t) {
#ifdef _MSC_VER
    FILETIME ft;
    memcpy(&ft, &t, sizeof(FILETIME));
    SYSTEMTIME stSystemTime;
    if (FileTimeToSystemTime(&ft, &stSystemTime)) {
        return std::to_string(stSystemTime.wDay) + "/" +
            std::to_string(stSystemTime.wMonth) + "/" +
            std::to_string(stSystemTime.wYear) + " " +
            std::to_string(stSystemTime.wHour) + ":" +
            std::to_string(stSystemTime.wMinute) + ":" +
            std::to_string(stSystemTime.wSecond);
    }
    return "";
#else
    std::time_t convfiletime = std::chrono::system_clock::to_time_t(t);
    return std::ctime(&convfiletime);
#endif
}

void DisplayFileInfo(const fs::directory_entry & entry, int level) {
    const auto filetime = fs::last_write_time(entry);
    const auto ofsize = ComputeFileSize(entry);
    std::cout << std::setw(level * 3) << " " << entry.path().filename() << ", "
        << SizeToString(ofsize)
        << ", modified: "
        << ElapsedToString(fs::file_time_type::clock::now() - filetime)
        << ", date: "
        << FileTimeToDate(filetime)
        << '\n';
}

void DisplayDirectoryTree(const fs::path& pathToShow, int level = 0) {
    if (fs::exists(pathToShow) && fs::is_directory(pathToShow)) {
        for (const auto& entry : fs::directory_iterator(pathToShow)) {
            auto filename = entry.path().filename();
            if (fs::is_directory(entry.status())) {
                std::cout << std::setw(level * 3) << "" << "[+] " << filename << '\n';
                DisplayDirectoryTree(entry, level + 1);
            }
            else if (fs::is_regular_file(entry.status()))
                DisplayFileInfo(entry, level);
            else
                std::cout << std::setw(level * 3) << "" << " [?]" << filename << '\n';
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        const fs::path pathToShow{ argc >= 2 ? argv[1] : fs::current_path() };

        std::cout << "listing files in the directory: " << fs::absolute(pathToShow) << '\n';
        std::cout << "current path is: " << fs::current_path() << '\n';

        DisplayDirectoryTree(pathToShow);
    }
    catch (const fs::filesystem_error& err) {
        std::cerr << "filesystem error! " << err.what() << '\n';
    }
    catch (...) {
        std::cerr << "unknown exception!\n";
    }
}