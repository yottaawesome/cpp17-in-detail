// par_exceptions.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

void ForEachTest() {
	std::vector<int> v(100);
	std::iota(v.begin(), v.end(), 0);

	std::for_each(std::execution::par, v.begin(), v.end(),
		[](int& i) { i += 10; });

	std::for_each_n(std::execution::par, v.begin(), v.size() / 2,
		[](int& i) { i += 10; });
}

void ReduceTest() {
	std::vector<int> v(100);
	std::iota(v.begin(), v.end(), 0);

	auto sum = std::reduce(std::execution::par, 
						   v.begin(), v.end(), 
						   /*init*/0);

	std::cout << sum << '\n';

auto sumTransformed = std::transform_reduce(std::execution::par,
	v.begin(),
	v.end(),
	0,
	std::plus<int>(),
	[](const int& i) { return i * 2; }
);

	std::cout << sumTransformed << '\n';
}

void ScanTest() {
	std::vector<int> v(10);
	std::iota(v.begin(), v.end(), 1);

	std::vector<int> sumsExclusive(v.size());
	std::exclusive_scan(std::execution::par, v.begin(), v.end(),
		sumsExclusive.begin(), 0);

	std::vector<int> sumsInclusive(v.size());
	std::inclusive_scan(std::execution::par, v.begin(), v.end(),
		sumsInclusive.begin());

	for (size_t i = 0; i < v.size(); ++i)
		std::cout << sumsExclusive[i] << ", " << sumsInclusive[i] << '\n';
}

int main() {
	ForEachTest();

	ReduceTest();

	ScanTest();

	return 0;
}

