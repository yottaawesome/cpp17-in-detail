// par_benchmark.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <algorithm>
#include <cmath>
#include <execution>
#include <iostream>
#include <list>
#include <numeric>

#include "simpleperf.h"

int main(int argc, const char* argv[]) {
    const size_t vecSize = argc > 1 ? atoi(argv[1]) : 6000000;
    std::cout << vecSize << '\n';
    std::vector<double> vec(vecSize, 0.5);
    std::vector out(vec);

    RunAndMeasure("std::transform seq", [&vec, &out] {
        std::transform(std::execution::seq, vec.begin(), vec.end(), out.begin(),
            [](double v) {
                return std::sin(v)*std::cos(v);
            }
        );
        return out.size();
    });

    RunAndMeasure("std::transform par", [&vec, &out] {
        std::transform(std::execution::par, vec.begin(), vec.end(), out.begin(),
            [](double v) {
                return std::sin(v)*std::cos(v);
            }
        );
        return out.size();
    });

    // using the identity: sin(2x) = 2 sin(x)cos(x)
    RunAndMeasure("std::transform par sin opt", [&vec, &out] {
        std::transform(std::execution::par, vec.begin(), vec.end(), out.begin(),
            [](double v) {
                return std::sin(2*v)*0.5;
            }
        );
        return out.size();
    });

    RunAndMeasure("std::accumulate", [&vec] {
        return std::accumulate(vec.begin(), vec.end(), 0.0);
    });

    RunAndMeasure("std::reduce, seq", [&vec] {
        return std::reduce(std::execution::seq, vec.begin(), vec.end(), 0.0);
    });

    // in MSVC par_unseq has the same implementation as "par"
    RunAndMeasure("std::reduce, par_unseq", [&vec] {
        return std::reduce(std::execution::par_unseq, vec.begin(), vec.end(), 0.0);
    });

    RunAndMeasure("std::reduce, par", [&vec] {
        return std::reduce(std::execution::par, vec.begin(), vec.end(), 0.0);
    });

    RunAndMeasure("std::find, seq", [&vec] {
        auto res = std::find(std::execution::seq, std::begin(vec), std::end(vec), 0.6);
        return res == std::end(vec) ? 0.0 : 1.0;
    });

    RunAndMeasure("std::sort, seq", [&vec] {
        std::sort(std::execution::seq, std::begin(vec), std::end(vec));
        return vec[0];
    });

    RunAndMeasure("std::sort, par", [&vec] {
        std::sort(std::execution::par, std::begin(vec), std::end(vec));
        return vec[0];
    });

    RunAndMeasure("std::find, par", [&vec] {
        auto res = std::find(std::execution::par, std::begin(vec), std::end(vec), 0.6);
        return res == std::end(vec) ? 0.0 : 1.0;
    });

    std::list<size_t> l(vecSize);
    std::iota(l.begin(), l.end(), 0);

    RunAndMeasure("std::find, list, seq", [&l, &vecSize] {
        auto res = std::find(std::execution::seq, std::begin(l), std::end(l), vecSize);
        return res == std::end(l);
    });

    RunAndMeasure("std::find, list, par", [&l, &vecSize] {
        auto res = std::find(std::execution::par, std::begin(l), std::end(l), vecSize);
        return res == std::end(l);
    });

    return 0;
}

