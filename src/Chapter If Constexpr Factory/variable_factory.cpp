#include <cassert>
#include <memory>
// variable_factory.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <type_traits>
#include <utility>
#include <iostream>
#include <string>

using namespace std::string_literals;

// before C++17:
// - enable_if_v - from C++14
// - is_constructible - from C++11
template <typename Concrete, typename... Ts>
std::enable_if_t<std::is_constructible<Concrete, Ts...>::value, std::unique_ptr<Concrete> >
constructArgsOld(Ts&&... params) {
	std::cout << __func__ << " templated..." << std::endl;
    return std::make_unique<Concrete>(std::forward<Ts>(params)...);
}

template <typename Concrete, typename... Ts>
std::enable_if_t<!std::is_constructible<Concrete, Ts...>::value, std::unique_ptr<Concrete> >
constructArgsOld(...) {
	std::cout << __func__ << "(...)" << std::endl;
    return nullptr;
}

// using C++17
// - if constexpr
// - is_constructible_v
// - fold expression to print arguments
template <typename Concrete, typename... Ts>
std::unique_ptr<Concrete> constructArgs(Ts&&... params) { 
	std::cout << __func__ << ": ";
	((std::cout << params << ", "), ...);
	std::cout << '\n';
    
	if constexpr (std::is_constructible_v<Concrete, Ts...>)
		return std::make_unique<Concrete>(std::forward<Ts>(params)...);
	else
		return nullptr;
}

class Investment {
public:
	virtual ~Investment() { }
	
	virtual void calcRisk() = 0;
};

class Stock : public Investment {
public:
	explicit Stock(const std::string&) { }
	
	void calcRisk() override { }
};

class Bond : public Investment {
public:
	explicit Bond(const std::string&, const std::string&, int) { }
	
	void calcRisk() override { }
};

class RealEstate : public Investment {
public:
	explicit RealEstate(const std::string&, double, int) { }
	
	void calcRisk() override { }
};

template <typename... Ts> 
std::unique_ptr<Investment> makeInvestment(const std::string &name, Ts&&... params) {
	std::cout << __func__ << ", " << name << std::endl;
	
	std::unique_ptr<Investment> pInv;
	
    if (name == "Stock")
		pInv = constructArgs<Stock, Ts...>(std::forward<Ts>(params)...);
    else if (name == "Bond")
		pInv = constructArgs<Bond, Ts...>(std::forward<Ts>(params)...);
    else if (name == "RealEstate")
		pInv = constructArgs<RealEstate, Ts...>(std::forward<Ts>(params)...);

    if (pInv)
        pInv->calcRisk(); // calc initial risk and cache result...
    else
	    std::cout << "nullptr from 'makeInvestment'" << std::endl;
	    
    return pInv;
}

int main() {
    auto s = "10"s;
    
    auto noArgs = makeInvestment("Stock");
    assert(!noArgs);
    
    auto pStock = makeInvestment("Stock", "abc");
    assert(pStock);
    
    auto pBond = makeInvestment("Bond", "xyz", "2210", 5);
    assert(pBond);
    
    auto pRealEstate = makeInvestment("RealEstate", "CA", 0.75, 10);
    assert(pRealEstate);
    
    auto nothing = makeInvestment("SomethingElse", '?');
    assert(!nothing);
}