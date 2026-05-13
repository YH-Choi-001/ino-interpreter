/**
 * @file mem_leak.h The plug-in for detecting memory leaks in test cases.
 * 
 * @copyright Copyright (c) 2026 YH Choi. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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