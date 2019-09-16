// variant_parsing_int_float_gcc.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <variant>
#include <map>
#include <charconv>
#include <cstring>
#include <optional>
#include <string>
#include <string_view>

class CmdLine {
public:
    using Arg = std::variant<int, std::string>;

private:
    std::map<std::string, Arg> mParsedArgs;

public:
    explicit CmdLine(int argc, const char** argv) { ParseArgs(argc, argv); }

    std::optional<Arg> Find(const std::string& name) const;

    void ParseArgs(int argc, const char** argv);
};

std::optional<CmdLine::Arg> CmdLine::Find(const std::string& name) const {
    if (const auto it = mParsedArgs.find(name); it != mParsedArgs.end())
        return it->second;

    return { };
}

// at the moment (Oct 2018) only MSVC supports floating point conversions
CmdLine::Arg TryParseString(std::string_view sv) {
    // try with float first
    int iResult = 0;
    const auto last = sv.data() + sv.size();
    const auto res = std::from_chars(sv.data(), last, iResult);
    if (res.ec != std::errc{} || res.ptr != last) {
        // if not possible, then just assume it's a string
        return std::string{sv};
    }

    return iResult;
}

void CmdLine::ParseArgs(int argc, const char** argv) {
    // the form: -argName value -argName value
    // unnamed? later...
    for (int i = 1; i < argc; i += 2) {
        if (argv[i][0] != '-')
            throw std::runtime_error("wrong command name");

        mParsedArgs[argv[i] + 1] = TryParseString(argv[i + 1]);
    }
}

int main(int argc, const char** argv) {
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " -paramInt <number> -paramText <string>\n";
        return 0;
    }

    try {
        CmdLine cmdLine(argc, argv);

        if (auto arg = cmdLine.Find("paramInt"); arg)
            std::cout << "paramInt is " << std::get<int>(*arg) << '\n';

        if (auto arg = cmdLine.Find("paramText"); arg)
            std::cout << "paramText is " << std::get<std::string>(*arg) << '\n';
    }
    catch (const std::bad_variant_access& err) {
        std::cerr << " ...err: accessing a wrong variant type, " << err.what() << '\n';
    }
    catch (const std::runtime_error &err) {
        std::cerr << " ...err: " << err.what() << '\n';
    }

    return 0;
}