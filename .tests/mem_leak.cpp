/**
 * @file mem_leak.cpp Replacement global new/delete operators that count allocations.
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
 */

#include "mem_leak.h"

#include <cstdlib>
#include <new>

#if (MEM_LEAK_DEBUG_LEVEL >= 2)
#include <cstdio>
#endif

namespace {
    long outstanding_allocation_count = 0;
}

long tests::mem_leak::get_outstanding_allocation_count() {
    return outstanding_allocation_count;
}

#if (MEM_LEAK_DEBUG_LEVEL >= 1)

namespace {
    void *counted_alloc(const std::size_t size) {
        void *const ptr = std::malloc(size == 0 ? 1 : size);
        if (ptr == nullptr) {
            throw std::bad_alloc();
        }
        outstanding_allocation_count++;
#if (MEM_LEAK_DEBUG_LEVEL >= 2)
        std::printf("new @ %p (len = %zu)\n", ptr, size);
#endif
        return ptr;
    }

    void counted_free(void *const ptr) noexcept {
        if (ptr == nullptr) {
            return;
        }
        outstanding_allocation_count--;
#if (MEM_LEAK_DEBUG_LEVEL >= 2)
        std::printf("del @ %p\n", ptr);
#endif
        std::free(ptr);
    }
}

void *operator new(const std::size_t size) {
    return counted_alloc(size);
}
void *operator new[](const std::size_t size) {
    return counted_alloc(size);
}
void operator delete(void *const ptr) noexcept {
    counted_free(ptr);
}
void operator delete[](void *const ptr) noexcept {
    counted_free(ptr);
}
void operator delete(void *const ptr, std::size_t) noexcept {
    counted_free(ptr);
}
void operator delete[](void *const ptr, std::size_t) noexcept {
    counted_free(ptr);
}

#endif // #if (MEM_LEAK_DEBUG_LEVEL >= 1)
