// searchers_benchmark.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <chrono>
#include <fstream>
#include <string_view>
#include <numeric>
#include <sstream>
#include "simpleperf.h"

using namespace std::literals;

const std::string_view LoremIpsumStrv{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
"sed do eiusmod tempor incididuntsuperlongwordsuper ut labore et dolore magna aliqua. Ut enim ad minim veniam, "
"quis nostrud exercitation ullamco laboris nisi ut aliquipsuperlongword ex ea commodo consequat. Duis aute "
"irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
"Excepteur sint occaecat cupidatatsuperlongword non proident, sunt in culpa qui officia deserunt mollit anim id est laborum." };

std::string GetNeedleString(int argc, const char** argv, const std::string &testString) {
    const auto testStringLen = testString.length();
    if (argc > 3) {
        const size_t tempLen = atoi(argv[3]);
        if (tempLen == 0) { // some word?
            std::cout << "needle is a string...\n";
            return argv[3];
        }
        else {
            const size_t PATTERN_LEN = tempLen > testStringLen ? testStringLen : tempLen;
            const int pos = argc > 4 ? atoi(argv[4]) : 0;

            if (pos == 0) {
                std::cout << "needle from the start...\n";
                return testString.substr(0, PATTERN_LEN);
            }
            else if (pos == 1) {
                std::cout << "needle from the center...\n";
                return testString.substr(testStringLen / 2 - PATTERN_LEN / 2 - 1, PATTERN_LEN);
            }
            else {
                std::cout << "needle from the end\n";               
                return testString.substr(testStringLen - PATTERN_LEN - 1, PATTERN_LEN);
            }
        }
    }
    
    // just take the 1/4 of the input string from the end...
    return testString.substr(testStringLen - testStringLen/4 - 1, testStringLen/4);
}

int main(int argc, const char** argv) {
    std::string testString{ LoremIpsumStrv };

    if (argc == 1) {
        std::cout << "searchers.exe filename iterations pattern_len pos\n";
        return 0;
    }

    if (argc > 1 && "nofile"s != argv[1]) {
        std::ifstream inFile(argv[1]);

        std::stringstream strStream;
        strStream << inFile.rdbuf();
        testString = strStream.str();
    }

    std::cout << "string length: " << testString.length() << '\n';

    const size_t ITERS = argc > 2 ? atoi(argv[2]) : 1000;
    std::cout << "test iterations: " << ITERS << '\n';

    const auto needle = GetNeedleString(argc, argv, testString);
    std::cout << "pattern length: " << needle.length() << '\n';

    RunAndMeasure("string::find", [&]() {
        for (size_t i = 0; i < ITERS; ++i)
        {
            std::size_t found = testString.find(needle);
            if (found == std::string::npos)
                std::cout << "The string " << needle << " not found\n";
        }
        return 0;
    });

    RunAndMeasure("default searcher", [&]() {
        for (size_t i = 0; i < ITERS; ++i)
        {
            auto it = std::search(testString.begin(), testString.end(),
                std::default_searcher(
                    needle.begin(), needle.end()));
            if (it == testString.end())
                std::cout << "The string " << needle << " not found\n";
        }
        return 0;
    });

    RunAndMeasure("boyer_moore_searcher init only", [&]() {
        for (size_t i = 0; i < ITERS; ++i)
        {
            std::boyer_moore_searcher b(needle.begin(), needle.end());
            DoNotOptimizeAway(&b);
        }
        return 0;
    });

    RunAndMeasure("boyer_moore_searcher", [&]() {
        for (size_t i = 0; i < ITERS; ++i)
        {
            auto it = std::search(testString.begin(), testString.end(),
                std::boyer_moore_searcher(
                    needle.begin(), needle.end()));
            if (it == testString.end())
                std::cout << "The string " << needle << " not found\n";
        }
        return 0;
    });

    RunAndMeasure("boyer_moore_horspool_searcher init only", [&]() {
        for (size_t i = 0; i < ITERS; ++i)
        {
            std::boyer_moore_horspool_searcher b(needle.begin(), needle.end());
            DoNotOptimizeAway(&b);
        }
        return 0;
    });

    RunAndMeasure("boyer_moore_horspool_searcher", [&]() {
        for (size_t i = 0; i < ITERS; ++i)
        {
            auto it = std::search(testString.begin(), testString.end(),
                std::boyer_moore_horspool_searcher(
                    needle.begin(), needle.end()));
            if (it == testString.end())
                std::cout << "The string " << needle << " not found\n";
        }
        return 0;
    });
}
