// dna_demo.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <string>
#include <algorithm>  // std::search
#include <vector>
#include <functional> // searchers
#include <iterator>
#include <sstream>

// A 65 01000 | 00 | 1  0
// C 67 01000 | 01 | 1  1
// G 71 01000 | 11 | 1  3
// T 84 01010 | 10 | 0  2
struct Nucleotide {
    enum class Type : uint8_t {
        A = 0,
        C = 1,
        G = 3,
        T = 2
    };
    
    Type mType;
    
    friend bool operator==(Nucleotide a, Nucleotide b) noexcept {
        return a.mType == b.mType;   
    }
    
    static char ToChar(Nucleotide t);
    static Nucleotide FromChar(char ch);
};

namespace std {
    template<> struct hash<Nucleotide> {
        size_t operator()(Nucleotide n) const noexcept {
            return std::hash<Nucleotide::Type>{}(n.mType);
        }
    };
}

char Nucleotide::ToChar(Nucleotide t) {
    switch (t.mType) {
    case Nucleotide::Type::A: return 'A';
    case Nucleotide::Type::C: return 'C';
    case Nucleotide::Type::G: return 'G';
    case Nucleotide::Type::T: return 'T';
    }
    return 0;
}

Nucleotide Nucleotide::FromChar(char ch) {
    return Nucleotide { static_cast<Nucleotide::Type>((ch >> 1) & 0x03) };
}

std::vector<Nucleotide> FromString(const std::string& s) {
    std::vector<Nucleotide> out;
    out.reserve(s.length());
    std::transform(std::cbegin(s), std::cend(s), 
                   std::back_inserter(out), Nucleotide::FromChar);
    return out;
}

std::string ToString(const std::vector<Nucleotide>& vec) {
    std::stringstream ss;
    std::ostream_iterator<char> out_it(ss);
    std::transform(std::cbegin(vec), std::cend(vec), out_it, Nucleotide::ToChar);
    return ss.str();
}

int main() {
    const std::vector<Nucleotide> dna = FromString("CTGATGTTAAGTCAACGCTGC");
    std::cout << ToString(dna) << '\n';
    const std::vector<Nucleotide> s = FromString("GCTGC");
    std::cout << ToString(s) << '\n';

    std::boyer_moore_horspool_searcher searcher(std::cbegin(s), std::cend(s));
    const auto it = std::search(std::cbegin(dna), std::cend(dna), searcher);
        
    if (it == std::cend(dna))
        std::cout << "The pattern " << ToString(s) << " not found\n";
    else {
        std::cout << "DNA matched at position: " 
                  << std::distance(std::cbegin(dna), it) << '\n';
    }
}
