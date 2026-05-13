/**
 * Unit tests for the argument class.
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

#include "../../test.h"

#include "../../../src/structs/Argument.h"

using ino_interpreter::structs::Argument;
using ino_interpreter::structs::util::Substring;

std::ostream &operator<<(std::ostream &os, const Substring &str) {
    const size_t len = str.getLength();
    for (size_t i = 0; i < len; i++) {
        os << str[i];
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Argument &str) {
    os << (Substring)str;
    return os;
}

namespace {

#define ASSERT_ARG_IS(arg,f,s) { \
    const float mul64 = (f) * 64.0f; \
    if (((f) == -0.0f) || mul64 == (long)mul64) { \
        ASSERT_EQUALS((float)arg, (float)(f)); \
    } else { \
        ASSERT_FLOAT_EQUALS((float)arg, (float)(f), 0.000005f); \
    } \
    ASSERT_EQUALS((const Substring)(arg), (s)); \
}

#define ASSERT_CONSTRUCT_OK(f,s) { \
    const Argument arg1(s); \
    ASSERT_ARG_IS(arg1,f,s); \
    const Argument arg2(arg1); \
    ASSERT_ARG_IS(arg2,f,s); \
}

TEST_BEGIN(empty_testcase)
    result.passed = true;
TEST_END()

TEST_BEGIN(constructor_memory_leak)
    ASSERT_CONSTRUCT_OK(0.0f, "");
TEST_END()

TEST_BEGIN(init_with_0)
    ASSERT_CONSTRUCT_OK(0.0f, "0");
TEST_END()

TEST_BEGIN(init_with_pos_0)
    ASSERT_CONSTRUCT_OK(0.0f, "+0");
TEST_END()

TEST_BEGIN(init_with_neg_0)
    ASSERT_CONSTRUCT_OK(-0.0f, "-0");
TEST_END()

TEST_BEGIN(init_with_1)
    ASSERT_CONSTRUCT_OK(1.0f, "1");
TEST_END()

TEST_BEGIN(init_with_pos_1)
    ASSERT_CONSTRUCT_OK(1.0f, "+1");
TEST_END()

TEST_BEGIN(init_with_neg_1)
    ASSERT_CONSTRUCT_OK(-1.0f, "-1");
TEST_END()

TEST_BEGIN(init_with_12345678)
    ASSERT_CONSTRUCT_OK(12345678.0f, "12345678");
TEST_END()

TEST_BEGIN(init_with_pos_12345678)
    ASSERT_CONSTRUCT_OK(12345678.0f, "+12345678");
TEST_END()

TEST_BEGIN(init_with_neg_12345678)
    ASSERT_CONSTRUCT_OK(-12345678.0f, "-12345678");
TEST_END()

TEST_BEGIN(init_with_1_0625)
    ASSERT_CONSTRUCT_OK(1.0625f, "1.0625");
TEST_END()

TEST_BEGIN(init_with_pos_1_0625)
    ASSERT_CONSTRUCT_OK(1.0625f, "+1.0625");
TEST_END()

TEST_BEGIN(init_with_neg_1_0625)
    ASSERT_CONSTRUCT_OK(-1.0625f, "-1.0625");
TEST_END()

TEST_BEGIN(init_with_p0625)
    ASSERT_CONSTRUCT_OK(0.0625f, ".0625");
TEST_END()

TEST_BEGIN(init_with_pos_p0625)
    ASSERT_CONSTRUCT_OK(0.0625f, "+.0625");
TEST_END()

TEST_BEGIN(init_with_neg_p0625)
    ASSERT_CONSTRUCT_OK(-0.0625f, "-.0625");
TEST_END()

TEST_BEGIN(init_with_hex_FACE)
    ASSERT_CONSTRUCT_OK(64206.0f, "0xFACE");
TEST_END()

TEST_BEGIN(init_with_pos_hex_FACE)
    ASSERT_CONSTRUCT_OK(64206.0f, "+0xFACE");
TEST_END()

TEST_BEGIN(init_with_neg_hex_FACE)
    ASSERT_CONSTRUCT_OK(-64206.0f, "-0xFACE");
TEST_END()

TEST_BEGIN(init_with_0_alpha)
    ASSERT_CONSTRUCT_OK(0.0f, "0asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_pos_0_alpha)
    ASSERT_CONSTRUCT_OK(0.0f, "+0asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_neg_0_alpha)
    ASSERT_CONSTRUCT_OK(-0.0f, "-0asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_1_alpha)
    ASSERT_CONSTRUCT_OK(1.0f, "1asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_pos_1_alpha)
    ASSERT_CONSTRUCT_OK(1.0f, "+1asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_neg_1_alpha)
    ASSERT_CONSTRUCT_OK(-1.0f, "-1asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_12345678_alpha)
    ASSERT_CONSTRUCT_OK(12345678.0f, "12345678asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_pos_12345678_alpha)
    ASSERT_CONSTRUCT_OK(12345678.0f, "+12345678asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_neg_12345678_alpha)
    ASSERT_CONSTRUCT_OK(-12345678.0f, "-12345678asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_pi_alpha)
    ASSERT_CONSTRUCT_OK(3.14159f, "3.141592654asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_pos_pi_alpha)
    ASSERT_CONSTRUCT_OK(3.14159f, "+3.141592654asdfghjkl");
    result.passed = true;
    const Argument arg("+3.141592654asdfghjkl");
    ASSERT_FLOAT_EQUALS((float)arg, 3.14159f, 0.000005f);
    ASSERT_EQUALS((const Substring)arg, "+3.141592654asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_neg_pi_alpha)
    ASSERT_CONSTRUCT_OK(-3.14159f, "-3.141592654asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_p25_alpha)
    ASSERT_CONSTRUCT_OK(0.25f, ".25asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_pos_p25_alpha)
    ASSERT_CONSTRUCT_OK(0.25f, "+.25asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_neg_p25_alpha)
    ASSERT_CONSTRUCT_OK(-0.25f, "-.25asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_alpha_pi)
    ASSERT_CONSTRUCT_OK(0.0f, "asdfghjkl3.141592654");
TEST_END()

TEST_BEGIN(init_with_alpha_pos_pi)
    ASSERT_CONSTRUCT_OK(0.0f, "asdfghjkl+3.141592654");
TEST_END()

TEST_BEGIN(init_with_alpha_neg_pi)
    ASSERT_CONSTRUCT_OK(0.0f, "asdfghjkl-3.141592654");
TEST_END()

TEST_BEGIN(init_with_alpha_p375)
    ASSERT_CONSTRUCT_OK(0.0f, "asdfghjkl.375");
TEST_END()

TEST_BEGIN(init_with_alpha_pos_p375)
    ASSERT_CONSTRUCT_OK(0.0f, "asdfghjkl+.375");
TEST_END()

TEST_BEGIN(init_with_alpha_neg_p375)
    ASSERT_CONSTRUCT_OK(0.0f, "asdfghjkl-.375");
TEST_END()

TEST_BEGIN(init_with_alpha)
    ASSERT_CONSTRUCT_OK(0.0f, "asdfghjkl");
TEST_END()

TEST_BEGIN(init_with_hello_world_str)
    ASSERT_CONSTRUCT_OK(0.0f, "\"Hello, world!\"");
TEST_END()

}

const testfunc_t functions [] = {
    test_empty_testcase,
    test_constructor_memory_leak,
    test_init_with_0,
    test_init_with_pos_0,
    test_init_with_neg_0,
    test_init_with_1,
    test_init_with_pos_1,
    test_init_with_neg_1,
    test_init_with_12345678,
    test_init_with_pos_12345678,
    test_init_with_neg_12345678,
    test_init_with_1_0625,
    test_init_with_pos_1_0625,
    test_init_with_neg_1_0625,
    test_init_with_p0625,
    test_init_with_pos_p0625,
    test_init_with_neg_p0625,
    test_init_with_hex_FACE,
    test_init_with_pos_hex_FACE,
    test_init_with_neg_hex_FACE,
    test_init_with_0_alpha,
    test_init_with_pos_0_alpha,
    test_init_with_neg_0_alpha,
    test_init_with_1_alpha,
    test_init_with_pos_1_alpha,
    test_init_with_neg_1_alpha,
    test_init_with_12345678_alpha,
    test_init_with_pos_12345678_alpha,
    test_init_with_neg_12345678_alpha,
    test_init_with_pi_alpha,
    test_init_with_pos_pi_alpha,
    test_init_with_neg_pi_alpha,
    test_init_with_p25_alpha,
    test_init_with_pos_p25_alpha,
    test_init_with_neg_p25_alpha,
    test_init_with_alpha_pi,
    test_init_with_alpha_pos_pi,
    test_init_with_alpha_neg_pi,
    test_init_with_alpha_p375,
    test_init_with_alpha_pos_p375,
    test_init_with_alpha_neg_p375,
    test_init_with_alpha,
    test_init_with_hello_world_str,
};

MAIN();
