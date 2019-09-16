// par_count_if.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <algorithm>
#include <execution>
#include <iostream>
#include <map>
#include <numeric>
#include <string_view>
#include <vector>
#include "simpleperf.h"

template <typename Policy, typename Iter, typename Func>
std::size_t CountIf(Policy policy, Iter first, Iter last, Func predicate) {
	return std::transform_reduce(policy,
		first,
		last,
		std::size_t(0),
		std::plus<std::size_t>{},
		[&predicate](const auto& v) {
		    return predicate(v) ? 1 : 0;
	    }
    );
}

int main(int argc, const char** argv) {
	const size_t vecSize = argc > 1 ? atoi(argv[1]) : 6000000;
	std::cout << vecSize << '\n';
	std::vector<int> vec(vecSize);

	std::iota(vec.begin(), vec.end(), 0);

	RunAndMeasure("CountIf seq", [&vec] {
		return CountIf(std::execution::seq, vec.begin(), vec.end(), [](int i) {return i % 3 == 0; });
	});

	RunAndMeasure("CountIf par", [&vec] {
		return CountIf(std::execution::par, vec.begin(), vec.end(), [](int i) {return i % 3 == 0; });
	});

	RunAndMeasure("std::count_if par", [&vec] {
		return std::count_if(std::execution::par, vec.begin(), vec.end(), [](int i) {return i % 3 == 0; });
	});

	//////////////////////////////////////
	// vector
	std::vector<int> v(100);
	std::iota(v.begin(), v.end(), 0);
	auto NumEven = CountIf(std::execution::par, v.begin(), v.end(),
		[](int i) { return i % 2 == 0; }
	);
	std::cout << NumEven << '\n';

	//////////////////////////////////////
	// string_view
	std::string_view sv = "Hello   Programming   Word";
	auto NumSpaces = CountIf(std::execution::par, sv.begin(), sv.end(),
		[](char ch) { return ch == ' '; }
	);
	std::cout << NumSpaces << '\n';

	//////////////////////////////////////
	// map
	std::map<std::string, int> CityAndPopulation { 
		{"Cracow", 765000},
		{"Warsaw", 1745000},
		{"London", 10313307},
		{"New York", 18593220},
		{"San Diego", 3107034} 
	};

	auto NumCitiesLargerThanMillion = CountIf(std::execution::par,
		CityAndPopulation.begin(), CityAndPopulation.end(),
		[](const std::pair<const std::string, int>& p) {
		    return p.second > 1000000; 
        }
	);
	std::cout << NumCitiesLargerThanMillion << '\n';

    return 0;
}

