#ifndef MEM_LEAK_H
#define MEM_LEAK_H

#include <cstddef>
#include <cstdlib>

#ifndef MEM_LEAK_DEBUG_LEVEL
#define MEM_LEAK_DEBUG_LEVEL 1
#endif

namespace tests {
    namespace mem_leak {
        static size_t malloc_count = 0;

        void reset_malloc_count();

        size_t get_malloc_count();

        bool has_memory_leaked();
    }
}

#if (MEM_LEAK_DEBUG_LEVEL == 0)
// use the default implementation
// void *operator new(const size_t size) {
//     return malloc(size);
// }
// void *operator new[](const size_t size) {
//     return malloc(size);
// }
// void operator delete(void *const ptr) {
//     free(ptr);
// }
// void operator delete[](void *const ptr) {
//     free(ptr);
// }

void tests::mem_leak::reset_malloc_count() {
    //
}

size_t tests::mem_leak::get_malloc_count() {
    return 0;
}

bool tests::mem_leak::has_memory_leaked() {
    return false;
}
#elif (MEM_LEAK_DEBUG_LEVEL == 1)

void *operator new(const size_t size) {
    tests::mem_leak::malloc_count++;
    return malloc(size);
}
void *operator new[](const size_t size) {
    tests::mem_leak::malloc_count++;
    return malloc(size);
}
void operator delete(void *const ptr) {
    tests::mem_leak::malloc_count--;
    free(ptr);
}
void operator delete[](void *const ptr) {
    tests::mem_leak::malloc_count--;
    free(ptr);
}

void tests::mem_leak::reset_malloc_count() {
    tests::mem_leak::malloc_count = 0;
}

size_t tests::mem_leak::get_malloc_count() {
    return tests::mem_leak::malloc_count;
}

bool tests::mem_leak::has_memory_leaked() {
    return tests::mem_leak::malloc_count != 0;
}
#elif (MEM_LEAK_DEBUG_LEVEL == 2)
#include <iostream>

void *operator new(const size_t size) {
    tests::mem_leak::malloc_count++;
    void *const ptr = malloc(size);
    std::cout << "new @ " << ptr << " (len = " << size << " )" << std::endl;
    return ptr;
}
void *operator new[](const size_t size) {
    tests::mem_leak::malloc_count++;
    void *const ptr = malloc(size);
    std::cout << "new @ " << ptr << " (len = " << size << " )" << std::endl;
    return ptr;
}
void operator delete(void *const ptr) {
    tests::mem_leak::malloc_count--;
    std::cout << "del @ " << ptr << std::endl;
    free(ptr);
}
void operator delete[](void *const ptr) {
    tests::mem_leak::malloc_count--;
    std::cout << "del @ " << ptr << std::endl;
    free(ptr);
}

void tests::mem_leak::reset_malloc_count() {
    tests::mem_leak::malloc_count = 0;
    std::cout << "tests::mem_leak::malloc_count resetted" << std::endl;
}

size_t tests::mem_leak::get_malloc_count() {
    return tests::mem_leak::malloc_count;
}

bool tests::mem_leak::has_memory_leaked() {
    return tests::mem_leak::malloc_count != 0;
}
#endif

#endif // #ifndef MEM_LEAK_H