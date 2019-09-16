// filesystem_compare.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <cassert>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
#ifdef _MSC_VER
    fs::path p1 = "C:/test"; 
    fs::path p2 = "C:/abc";
    assert(p1 > p2);
    assert(p1.compare(p2) > 0);

    p1 = "C:/test"; 
    p2 = "abc/xyz";
    assert(p1.has_root_directory());
    assert(p2.is_relative());
    assert(p1 > p2);
    assert(p1.compare(p2) > 0);

    fs::path p3 = "/usr/a/b/c"; // on Windows it's converted to native format
    fs::path p4 = "\\usr/a\\b/c"; 
    assert(p3 == p4);
    assert(p3.compare(p4) == 0);
#endif

    fs::path p5 = "/usr/a/b/c";
    fs::path p6 = "/usr/a/b/c";
    assert(p5 == p6);
    assert(p5.compare(p6) == 0);

    p5 = "/usr/a/b/c";
    p6 = "/usr/a/b/c/d";
    assert(p5 < p6);
    assert(p5.compare(p6) < 0);
}