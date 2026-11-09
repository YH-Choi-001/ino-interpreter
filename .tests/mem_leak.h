/**
 * @file mem_leak.h Memory leak detection for GoogleTest test cases.
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

#ifndef MEM_LEAK_H
#define MEM_LEAK_H

#include <cstddef>

#include <gtest/gtest.h>

/**
 * Debug levels (set with -DMEM_LEAK_DEBUG_LEVEL=n when compiling mem_leak.cpp):
 *   0 - leak detection disabled
 *   1 - count outstanding allocations (default)
 *   2 - count outstanding allocations and trace every new/delete to stdout
 */
#ifndef MEM_LEAK_DEBUG_LEVEL
#define MEM_LEAK_DEBUG_LEVEL 1
#endif

namespace tests {
    namespace mem_leak {
        /**
         * @return the number of `new` allocations not yet matched by a `delete`,
         * counted since the start of the program.
         */
        long get_outstanding_allocation_count();

        /**
         * A GoogleTest fixture that fails a test if the test body
         * allocates with `new` more times than it frees with `delete`.
         */
        class MemoryLeakCheckedTest : public ::testing::Test {
            private:
                long baseline;
            protected:
                void SetUp() override {
                    baseline = get_outstanding_allocation_count();
                }
                void TearDown() override {
                    // GoogleTest itself allocates to record failures,
                    // so the count is only meaningful for an otherwise passing test.
                    if (HasFailure()) {
                        return;
                    }
                    const long leaked = get_outstanding_allocation_count() - baseline;
                    EXPECT_EQ(leaked, 0) << "Memory leak! You forgot " << leaked << " delete(s).";
                }
        };
    }
}

#endif // #ifndef MEM_LEAK_H
