// conversion_benchmark.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <algorithm>
#include <charconv>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// from https://stackoverflow.com/questions/33975479/escape-and-clobber-equivalent-in-msvc
/**
 * Call doNotOptimizeAway(var) against variables that you use for
 * benchmarking but otherwise are useless. The compiler tends to do a
 * good job at eliminating unused variables, and this function fools
 * it into thinking var is in fact needed.
 */
#ifdef _MSC_VER

#pragma optimize("", off)

template <class T>
void DoNotOptimizeAway(T&& datum) {
    datum = datum;
}

#pragma optimize("", on)

#elif defined(__clang__)

template <class T>
__attribute__((__optnone__)) void DoNotOptimizeAway(T&& /* datum */) {}

#else

template <class T>
void DoNotOptimizeAway(T&& datum) {
    asm volatile("" : "+r" (datum));
}

#endif

template <typename TFunc> void RunAndMeasure(const char* title, TFunc func) {
    auto ret = func();
    ret = func();
    DoNotOptimizeAway(ret);
    const auto start = std::chrono::steady_clock::now();
    ret = func();
    const auto end = std::chrono::steady_clock::now();
    DoNotOptimizeAway(ret);
    std::cout << title << ": " << std::chrono::duration <double, std::milli>(end - start).count() << " ms\n";
}

std::vector<int> GenRandVecOfNumbers(size_t count) {
    std::vector<int> out(count);

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::generate_n(std::begin(out), count, [&dist, &rng] {return dist(rng); });

    return out;
}

void CheckVectors(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        std::cout << "wrong size!\n";
        return;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i])
            std::cout << "error! " << i << " " << a[i] << " !=  " << b[i] << '\n';
    }
}

void Benchmark(size_t ITERS, size_t vecSize) {
    const auto numIntVec = GenRandVecOfNumbers(vecSize);
    std::vector<std::string> numStrVec(numIntVec.size());
    std::vector<int> numBackIntVec(numIntVec.size());

    std::string strTemp(15, ' ');

    //
    // from_chars/to_chars
    //

    RunAndMeasure("to_chars", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numIntVec.size(); ++i) {
                const auto res = std::to_chars(strTemp.data(), strTemp.data() + strTemp.size(), numIntVec[i]);
                numStrVec[i] = std::string_view(strTemp.data(), res.ptr - strTemp.data());
            }
            DoNotOptimizeAway(numStrVec.data());
        }
        return numStrVec.size();
    });

    RunAndMeasure("from_chars", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numStrVec.size(); ++i) {
                const auto &str{ numStrVec[i] };
                std::from_chars(str.data(), str.data() + str.size(), numBackIntVec[i]);
            }
            DoNotOptimizeAway(numBackIntVec.data());
        }
        return numBackIntVec.size();
    });

    CheckVectors(numIntVec, numBackIntVec);

    //
    // to_string / stoi
    //

    RunAndMeasure("to_string", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numStrVec.size(); ++i)
                numStrVec[i] = std::to_string(numIntVec[i]);

            DoNotOptimizeAway(numStrVec.data());
        }
        return numStrVec.size();
    });

    RunAndMeasure("stoi", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numStrVec.size(); ++i)
                numBackIntVec[i] = std::stoi(numStrVec[i]);

            DoNotOptimizeAway(numBackIntVec.data());
        }
        return numBackIntVec.size();
    });

    CheckVectors(numIntVec, numBackIntVec);

    //
    // sprintf / atoi
    //

    RunAndMeasure("sprintf", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numIntVec.size(); ++i) {
                auto res = snprintf(strTemp.data(), 15, "%d", numIntVec[i]);
                numStrVec[i] = std::string_view(strTemp.data(), (strTemp.data() + res) - strTemp.data());
            }
            DoNotOptimizeAway(numStrVec.data());
        }
        return numStrVec.size();
    });

    RunAndMeasure("atoi", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numStrVec.size(); ++i)
                numBackIntVec[i] = atoi(numStrVec[i].c_str());

            DoNotOptimizeAway(numBackIntVec.data());
        }
        return numBackIntVec.size();
    });

    // ostringstream / istringstream

    RunAndMeasure("otringstream", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numStrVec.size(); ++i) {
                std::ostringstream ss;
                ss << numIntVec[i];
                numStrVec[i] = ss.str();
            }
            DoNotOptimizeAway(numStrVec.data());
        }
        return numStrVec.size();
    });

    RunAndMeasure("stringstream", [&]() {
        for (size_t iter = 0; iter < ITERS; ++iter) {
            for (size_t i = 0; i < numStrVec.size(); ++i) {
                std::istringstream ss(numStrVec[i]);
                ss >> numBackIntVec[i];
            }
            DoNotOptimizeAway(numBackIntVec.data());
        }
        return numBackIntVec.size();
    });
}

int main(int argc, const char** argv) { 
    const size_t ITERS = argc > 1 ? atoi(argv[1]) : 1000;
    std::cout << "test iterations: " << ITERS << '\n';
    const size_t VECSIZE = argc > 2 ? atoi(argv[2]) : 1000;
    std::cout << "vector size: " << VECSIZE << '\n';

    Benchmark(ITERS, VECSIZE);
}
