// aligned_new.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <cassert>
#include <iostream>
#include <memory>
#include <new>
#include <vector>

#if defined(_WIN32) || defined(__CYGWIN__)
#    include <malloc.h> // _aligned_malloc/_aligned_free

    void* custom_aligned_alloc(size_t size, size_t alignment) {
        return _aligned_malloc(size, alignment);
    }
    void custom_aligned_free(void* ptr) {
        _aligned_free(ptr);
    }
#else
#    include <cstdint>  // aligned_alloc from C11

    void* custom_aligned_alloc(size_t size, size_t alignment) {
        return std::aligned_alloc(alignment, size);
    }
    void custom_aligned_free(void* ptr) {
        std::free(ptr);
    }
#endif

void* operator new(std::size_t size, std::align_val_t align) {
    auto ptr = custom_aligned_alloc(size, static_cast<std::size_t>(align));

    if (!ptr)
        throw std::bad_alloc{};

    std::cout << "new: " << size << ", align: " << static_cast<std::size_t>(align) << ", ptr: " << ptr << '\n';

    return ptr;
}

void operator delete(void* ptr, std::size_t size, std::align_val_t align) noexcept {
    std::cout << "delete: " << size << ", align: " << static_cast<std::size_t>(align) << ", ptr : " << ptr << '\n';
    custom_aligned_free(ptr);
}

void operator delete(void* ptr, std::align_val_t align) noexcept {
    std::cout << "delete: align: " << static_cast<std::size_t>(align) << ", ptr : " << ptr << '\n';
    custom_aligned_free(ptr);
}

struct alignas(32) Vec3dAVX {
    double x, y, z;
};

int main() {
    std::cout << "__STDCPP_DEFAULT_NEW_ALIGNMENT__ is " << __STDCPP_DEFAULT_NEW_ALIGNMENT__ << std::endl;

    std::cout << "sizeof(Vec3dAVX) is " << sizeof(Vec3dAVX) << '\n';
    std::cout << "alignof(Vec3dAVX) is " << alignof(Vec3dAVX) << '\n';

    {
        std::cout << "---- new Vec3dAVX[10]\n";
        auto pVec = new Vec3dAVX[10];
        assert(reinterpret_cast<uintptr_t>(pVec) % alignof(Vec3dAVX) == 0);
        delete[] pVec;
    }

    {
        std::cout << "---- new int[10]\n";
        auto p2 = new int[10];
        delete[] p2;
    }

    {
        std::cout << "---- vector<Vec3dAVX>\n";
        std::vector<Vec3dAVX> vec;
        vec.push_back({});
        vec.push_back({});
        vec.push_back({});
        assert(reinterpret_cast<uintptr_t>(vec.data()) % alignof(Vec3dAVX) == 0);
    }
    
    {
        std::cout << "---- unique_ptr<Vec3dAVX[]>\n";
        auto pUnique = std::make_unique<Vec3dAVX[]>(10);
    }
}