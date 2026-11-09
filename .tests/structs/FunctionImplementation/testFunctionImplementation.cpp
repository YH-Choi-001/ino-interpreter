/**
 * Unit tests for the function implementation class.
 * 
 * Copyright (c) 2026 YH Choi. All rights reserved.
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

#include <gtest/gtest.h>

#include "../../mem_leak.h"
#include "../../printers.h"

#include "../../../src/structs/FunctionImplementation.h"

using ino_interpreter::structs::FunctionImplementation;
using ino_interpreter::structs::FunctionCall;
using ino_interpreter::structs::Argument;
using ino_interpreter::structs::util::Substring;

class FunctionImplementationTest : public tests::mem_leak::MemoryLeakCheckedTest {};

namespace {

#define FCALL_0 ("in()")
#define FCALL_1 ("in(1)")
#define FCALL_2 ("in(1, 2)")
#define FCALL_3 ("in(1, 2, 3)")
#define FCALL_4 ("in(1, 2, 3, 4)")
#define FCALL_5 ("in(1, 2, 3, 4, 5)")
#define FCALL_6 ("in(1, 2, 3, 4, 5, 6)")
#define FCALL_7 ("in(1, 2, 3, 4, 5, 6, 7)")
#define FCALL_8 ("in(1, 2, 3, 4, 5, 6, 7, 8)")
#define FCALL_9 ("in(1, 2, 3, 4, 5, 6, 7, 8, 9)")
#define FCALL_10 ("in(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)")

#define LAMBDA_RET_VAL(n) (-65.0625 + 7.125 * (n))
#define _LAMBDA_RET(n) -> float { return (LAMBDA_RET_VAL(n)); }
#define LAMBDA_0 []() _LAMBDA_RET(0)
#define LAMBDA_1 [](Argument) _LAMBDA_RET(1)
#define LAMBDA_2 [](Argument, Argument) _LAMBDA_RET(2)
#define LAMBDA_3 [](Argument, Argument, Argument) _LAMBDA_RET(3)
#define LAMBDA_4 [](Argument, Argument, Argument, Argument) _LAMBDA_RET(4)
#define LAMBDA_5 [](Argument, Argument, Argument, Argument, Argument) _LAMBDA_RET(5)
#define LAMBDA_6 [](Argument, Argument, Argument, Argument, Argument, Argument) _LAMBDA_RET(6)
#define LAMBDA_7 [](Argument, Argument, Argument, Argument, Argument, Argument, Argument) _LAMBDA_RET(7)
#define LAMBDA_8 [](Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument) _LAMBDA_RET(8)
#define LAMBDA_9 [](Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument) _LAMBDA_RET(9)
#define LAMBDA_10 [](Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument) _LAMBDA_RET(10)

#define IMPLEMENTATION_NOT_FOUND (-999404)
#define LAMBDA_NULLPTR_0 (FunctionImplementation::return_t(*)())(nullptr)
#define LAMBDA_NULLPTR_1 (FunctionImplementation::return_t(*)(Argument))(nullptr)
#define LAMBDA_NULLPTR_2 (FunctionImplementation::return_t(*)(Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_3 (FunctionImplementation::return_t(*)(Argument, Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_4 (FunctionImplementation::return_t(*)(Argument, Argument, Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_5 (FunctionImplementation::return_t(*)(Argument, Argument, Argument, Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_6 (FunctionImplementation::return_t(*)(Argument, Argument, Argument, Argument, Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_7 (FunctionImplementation::return_t(*)(Argument, Argument, Argument, Argument, Argument, Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_8 (FunctionImplementation::return_t(*)(Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_9 (FunctionImplementation::return_t(*)(Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument))(nullptr)
#define LAMBDA_NULLPTR_10 (FunctionImplementation::return_t(*)(Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument, Argument))(nullptr)

#define ARGCOUNT_MISMATCH (-999003)

TEST_F(FunctionImplementationTest, empty_testcase) {
}

TEST_F(FunctionImplementationTest, func_ptr_constructor_memory_leak) {
    const FunctionImplementation impl(LAMBDA_0);
}

TEST_F(FunctionImplementationTest, copy_constructor_memory_leak) {
    const FunctionImplementation impl_0(LAMBDA_0);
    const FunctionImplementation impl_1(impl_0);
}

#define ASSERT_CONSTRUCTOR_ARG_COUNT_EQUALS(n, ...) { \
    const FunctionImplementation impl(__VA_ARGS__); \
    EXPECT_EQ(impl.getArgCount(), n); \
}

#define ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS(n, v, ...) { \
    const FunctionImplementation impl(__VA_ARGS__); \
    const FunctionCall fcall(FCALL_##n); \
    EXPECT_EQ(impl.execute(fcall), v); \
}

#define ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_DEFAULT(n, ...) { \
    ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS(n, LAMBDA_RET_VAL(n), __VA_ARGS__); \
}

#define ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_IMPLEMENTATION_NOT_FOUND(n, ...) { \
    ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS(n, IMPLEMENTATION_NOT_FOUND, __VA_ARGS__); \
}

#define ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_ARGCOUNT_MISMATCH(n, ...) { \
    ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS(n, ARGCOUNT_MISMATCH, __VA_ARGS__); \
}

#define TEST_FUNC_PTR_CONSTRUCTOR_ARG_COUNT(n) \
TEST_F(FunctionImplementationTest, func_ptr_constructor_arg_count_##n) { \
    ASSERT_CONSTRUCTOR_ARG_COUNT_EQUALS(n, LAMBDA_##n); \
}

#define TEST_FUNC_PTR_CONSTRUCTOR_RETURN_VALUES(n) \
TEST_F(FunctionImplementationTest, func_ptr_constructor_ret_val_##n) { \
    ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_DEFAULT(n, LAMBDA_##n); \
}

#define TEST_COPY_CONSTRUCTOR_ARG_COUNT(n) \
TEST_F(FunctionImplementationTest, copy_constructor_arg_count_##n) { \
    const FunctionImplementation impl_0(LAMBDA_##n); \
    ASSERT_CONSTRUCTOR_ARG_COUNT_EQUALS(n, impl_0); \
}

#define TEST_COPY_CONSTRUCTOR_RETURN_VALUES(n) \
TEST_F(FunctionImplementationTest, copy_constructor_ret_val_##n) { \
    const FunctionImplementation impl_0(LAMBDA_##n); \
    ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_DEFAULT(n, impl_0); \
}

#define TEST_FUNC_PTR_CONSTRUCTOR_ARG_COUNT_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_F(FunctionImplementationTest, func_ptr_constructor_arg_count_with_nullptr_implementation_##n) { \
    ASSERT_CONSTRUCTOR_ARG_COUNT_EQUALS(n, LAMBDA_NULLPTR_##n); \
}

#define TEST_FUNC_PTR_CONSTRUCTOR_RETURN_VALUES_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_F(FunctionImplementationTest, func_ptr_constructor_ret_val_with_nullptr_implementation_##n) { \
    ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_IMPLEMENTATION_NOT_FOUND(n, LAMBDA_NULLPTR_##n); \
}

#define TEST_COPY_CONSTRUCTOR_ARG_COUNT_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_F(FunctionImplementationTest, copy_constructor_arg_count_with_nullptr_implementation_##n) { \
    const FunctionImplementation impl_0(LAMBDA_NULLPTR_##n); \
    ASSERT_CONSTRUCTOR_ARG_COUNT_EQUALS(n, impl_0); \
}

#define TEST_COPY_CONSTRUCTOR_RETURN_VALUES_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_F(FunctionImplementationTest, copy_constructor_ret_val_with_nullptr_implementation_##n) { \
    const FunctionImplementation impl_0(LAMBDA_NULLPTR_##n); \
    ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_IMPLEMENTATION_NOT_FOUND(n, impl_0); \
}

#define TEST_FUNC_PTR_CONSTRUCTOR_RETURN_VALUES_FOR_ARGCOUNT_MISMATCH(n) \
TEST_F(FunctionImplementationTest, func_ptr_constructor_ret_val_for_argcount_mismatch_##n) { \
    if ((n) == 4) { \
        ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_ARGCOUNT_MISMATCH(n, LAMBDA_3); \
    } else { \
        ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_ARGCOUNT_MISMATCH(n, LAMBDA_4); \
    } \
}

#define TEST_COPY_CONSTRUCTOR_RETURN_VALUES_FOR_ARGCOUNT_MISMATCH(n) \
TEST_F(FunctionImplementationTest, copy_constructor_ret_val_for_argcount_mismatch_##n) { \
    if ((n) == 4) { \
        const FunctionImplementation impl_0(LAMBDA_3); \
        ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_ARGCOUNT_MISMATCH(n, impl_0); \
    } else { \
        const FunctionImplementation impl_0(LAMBDA_4); \
        ASSERT_CONSTRUCTOR_RETURN_VALUE_EQUALS_ARGCOUNT_MISMATCH(n, impl_0); \
    } \
}


#define TEST_FOR_N_ARGS(n) \
TEST_FUNC_PTR_CONSTRUCTOR_ARG_COUNT(n) \
TEST_FUNC_PTR_CONSTRUCTOR_RETURN_VALUES(n) \
TEST_COPY_CONSTRUCTOR_ARG_COUNT(n) \
TEST_COPY_CONSTRUCTOR_RETURN_VALUES(n) \
TEST_FUNC_PTR_CONSTRUCTOR_ARG_COUNT_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_FUNC_PTR_CONSTRUCTOR_RETURN_VALUES_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_COPY_CONSTRUCTOR_ARG_COUNT_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_COPY_CONSTRUCTOR_RETURN_VALUES_WITH_NULLPTR_IMPLEMENTATION(n) \
TEST_FUNC_PTR_CONSTRUCTOR_RETURN_VALUES_FOR_ARGCOUNT_MISMATCH(n) \
TEST_COPY_CONSTRUCTOR_RETURN_VALUES_FOR_ARGCOUNT_MISMATCH(n) \

TEST_FOR_N_ARGS(0)
TEST_FOR_N_ARGS(1)
TEST_FOR_N_ARGS(2)
TEST_FOR_N_ARGS(3)
TEST_FOR_N_ARGS(4)
TEST_FOR_N_ARGS(5)
TEST_FOR_N_ARGS(6)
TEST_FOR_N_ARGS(7)
TEST_FOR_N_ARGS(8)
TEST_FOR_N_ARGS(9)
TEST_FOR_N_ARGS(10)

}

