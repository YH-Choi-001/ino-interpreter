/**
 * Unit tests for the function call class.
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

#include "../../../src/structs/FunctionCall.h"

using ino_interpreter::structs::FunctionCall;
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

std::ostream &operator<<(std::ostream &os, const FunctionCall &fc) {
    os << (Substring)fc.getIdentifier() << "(";
    for (size_t i = 0; i < fc.getArgCount(); i++) {
        const Argument *const arg = fc.getArg(i);
        if (i > 0) {
            os << ", ";
        }
        if (arg == nullptr) {
            os << "null";
        } else {
            os << (*arg);
        }
    }
    os << ")";
    return os;
}

namespace {

TEST_BEGIN(empty_testcase)
    result.passed = true;
TEST_END()

TEST_BEGIN(constructor_memory_leak)
    result.passed = true;
    const FunctionCall fcall("foo()");
TEST_END()

TEST_BEGIN(init_with_foo_no_parenthesis)
    result.passed = true;
    const FunctionCall fcall("foo");
    ASSERT_EQUALS(fcall.getIdentifier(), "foo");
    ASSERT_EQUALS(fcall.getArgCount(), 0);
    ASSERT_IS_NULLPTR(fcall.getArg(0));
    ASSERT_IS_NULLPTR(fcall.getArg(1));
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_foo)
    result.passed = true;
    const FunctionCall fcall("foo()");
    ASSERT_EQUALS(fcall.getIdentifier(), "foo");
    ASSERT_EQUALS(fcall.getArgCount(), 0);
    ASSERT_IS_NULLPTR(fcall.getArg(0));
    ASSERT_IS_NULLPTR(fcall.getArg(1));
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_exit_2)
    result.passed = true;
    const FunctionCall fcall("exit(2)");
    ASSERT_EQUALS(fcall.getIdentifier(), "exit");
    ASSERT_EQUALS(fcall.getArgCount(), 1);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), 2.0f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "2");
    ASSERT_IS_NULLPTR(fcall.getArg(1));
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_exit_neg_17)
    result.passed = true;
    const FunctionCall fcall("exit(-17)");
    ASSERT_EQUALS(fcall.getIdentifier(), "exit");
    ASSERT_EQUALS(fcall.getArgCount(), 1);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), -17.0f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "-17");
    ASSERT_IS_NULLPTR(fcall.getArg(1));
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_exit_pos_hex_FACE)
    result.passed = true;
    const FunctionCall fcall("exit(+0xFACE)");
    ASSERT_EQUALS(fcall.getIdentifier(), "exit");
    ASSERT_EQUALS(fcall.getArgCount(), 1);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), 64206.0f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "+0xFACE");
    ASSERT_IS_NULLPTR(fcall.getArg(1));
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_exit_neg_hex_FACE)
    result.passed = true;
    const FunctionCall fcall("exit(-0xFACE)");
    ASSERT_EQUALS(fcall.getIdentifier(), "exit");
    ASSERT_EQUALS(fcall.getArgCount(), 1);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), -64206.0f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "-0xFACE");
    ASSERT_IS_NULLPTR(fcall.getArg(1));
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_sin_neg_p0625)
    result.passed = true;
    const FunctionCall fcall("sin(-.0625)");
    ASSERT_EQUALS(fcall.getIdentifier(), "sin");
    ASSERT_EQUALS(fcall.getArgCount(), 1);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), -0.0625f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "-.0625");
    ASSERT_IS_NULLPTR(fcall.getArg(1));
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_atan2)
    result.passed = true;
    const FunctionCall fcall("atan2(-.0625, +8.375)");
    ASSERT_EQUALS(fcall.getIdentifier(), "atan2");
    ASSERT_EQUALS(fcall.getArgCount(), 2);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), -0.0625f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "-.0625");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(1));
    ASSERT_EQUALS((float)(*fcall.getArg(1)), +8.375f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(1)), "+8.375");
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_digital_write)
    result.passed = true;
    const FunctionCall fcall("digitalWrite(13, 1)");
    ASSERT_EQUALS(fcall.getIdentifier(), "digitalWrite");
    ASSERT_EQUALS(fcall.getArgCount(), 2);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), 13);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "13");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(1));
    ASSERT_EQUALS((float)(*fcall.getArg(1)), 1);
    ASSERT_EQUALS((Substring)(*fcall.getArg(1)), "1");
    ASSERT_IS_NULLPTR(fcall.getArg(2));
    ASSERT_IS_NULLPTR(fcall.getArg(3));
    ASSERT_IS_NULLPTR(fcall.getArg(4));
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_baro)
    result.passed = true;
    const FunctionCall fcall("  qm.baro     (  +.25 ,  -3.125   , .875  , 0x818   , -.5   )   ");
    ASSERT_EQUALS(fcall.getIdentifier(), "qm.baro");
    ASSERT_EQUALS(fcall.getArgCount(), 5);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), 0.25f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "+.25");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(1));
    ASSERT_EQUALS((float)(*fcall.getArg(1)), -3.125f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(1)), "-3.125");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(2));
    ASSERT_EQUALS((float)(*fcall.getArg(2)), 0.875f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(2)), ".875");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(3));
    ASSERT_EQUALS((float)(*fcall.getArg(3)), 0x818);
    ASSERT_EQUALS((Substring)(*fcall.getArg(3)), "0x818");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(4));
    ASSERT_EQUALS((float)(*fcall.getArg(4)), -0.5f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(4)), "-.5");
    ASSERT_IS_NULLPTR(fcall.getArg(5));
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

TEST_BEGIN(init_with_baro_and_constants)
    result.passed = true;
    const FunctionCall fcall("  qm.baro     (  +.25 ,  -3.125   , .875  , HIGH-1.8356   , -.5qwer   ,  0x818    )   ");
    ASSERT_EQUALS(fcall.getIdentifier(), "qm.baro");
    ASSERT_EQUALS(fcall.getArgCount(), 6);
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(0));
    ASSERT_EQUALS((float)(*fcall.getArg(0)), 0.25f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(0)), "+.25");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(1));
    ASSERT_EQUALS((float)(*fcall.getArg(1)), -3.125f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(1)), "-3.125");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(2));
    ASSERT_EQUALS((float)(*fcall.getArg(2)), 0.875f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(2)), ".875");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(3));
    ASSERT_EQUALS((float)(*fcall.getArg(3)), 0.0f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(3)), "HIGH-1.8356");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(4));
    ASSERT_EQUALS((float)(*fcall.getArg(4)), -0.5f);
    ASSERT_EQUALS((Substring)(*fcall.getArg(4)), "-.5qwer");
    ASSERT_IS_NOT_NULLPTR(fcall.getArg(5));
    ASSERT_EQUALS((float)(*fcall.getArg(5)), 0x818);
    ASSERT_EQUALS((Substring)(*fcall.getArg(5)), "0x818");
    ASSERT_IS_NULLPTR(fcall.getArg(6));
    ASSERT_IS_NULLPTR(fcall.getArg(7));
    ASSERT_IS_NULLPTR(fcall.getArg(8));
    ASSERT_IS_NULLPTR(fcall.getArg(9));
TEST_END()

}

const testfunc_t functions [] = {
    test_empty_testcase,
    test_constructor_memory_leak,
    test_init_with_foo_no_parenthesis,
    test_init_with_foo,
    test_init_with_exit_2,
    test_init_with_exit_neg_17,
    test_init_with_exit_pos_hex_FACE,
    test_init_with_exit_neg_hex_FACE,
    test_init_with_sin_neg_p0625,
    test_init_with_atan2,
    test_init_with_digital_write,
    test_init_with_baro,
    test_init_with_baro_and_constants,
};

MAIN();
