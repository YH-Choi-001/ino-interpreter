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

#include <gtest/gtest.h>

#include "../../mem_leak.h"
#include "../../printers.h"

#include "../../../src/structs/FunctionCall.h"

using ino_interpreter::structs::FunctionCall;
using ino_interpreter::structs::Argument;
using ino_interpreter::structs::util::Substring;

class FunctionCallTest : public tests::mem_leak::MemoryLeakCheckedTest {};

namespace {

TEST_F(FunctionCallTest, empty_testcase) {
}

TEST_F(FunctionCallTest, constructor_memory_leak) {
    const FunctionCall fcall("foo()");
}

TEST_F(FunctionCallTest, init_with_foo_no_parenthesis) {
    const FunctionCall fcall("foo");
    EXPECT_EQ(fcall.getIdentifier(), "foo");
    EXPECT_EQ(fcall.getArgCount(), 0);
    EXPECT_EQ(fcall.getArg(0), nullptr);
    EXPECT_EQ(fcall.getArg(1), nullptr);
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_foo) {
    const FunctionCall fcall("foo()");
    EXPECT_EQ(fcall.getIdentifier(), "foo");
    EXPECT_EQ(fcall.getArgCount(), 0);
    EXPECT_EQ(fcall.getArg(0), nullptr);
    EXPECT_EQ(fcall.getArg(1), nullptr);
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_exit_2) {
    const FunctionCall fcall("exit(2)");
    EXPECT_EQ(fcall.getIdentifier(), "exit");
    EXPECT_EQ(fcall.getArgCount(), 1);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), 2.0f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "2");
    EXPECT_EQ(fcall.getArg(1), nullptr);
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_exit_neg_17) {
    const FunctionCall fcall("exit(-17)");
    EXPECT_EQ(fcall.getIdentifier(), "exit");
    EXPECT_EQ(fcall.getArgCount(), 1);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), -17.0f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "-17");
    EXPECT_EQ(fcall.getArg(1), nullptr);
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_exit_pos_hex_FACE) {
    const FunctionCall fcall("exit(+0xFACE)");
    EXPECT_EQ(fcall.getIdentifier(), "exit");
    EXPECT_EQ(fcall.getArgCount(), 1);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), 64206.0f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "+0xFACE");
    EXPECT_EQ(fcall.getArg(1), nullptr);
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_exit_neg_hex_FACE) {
    const FunctionCall fcall("exit(-0xFACE)");
    EXPECT_EQ(fcall.getIdentifier(), "exit");
    EXPECT_EQ(fcall.getArgCount(), 1);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), -64206.0f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "-0xFACE");
    EXPECT_EQ(fcall.getArg(1), nullptr);
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_sin_neg_p0625) {
    const FunctionCall fcall("sin(-.0625)");
    EXPECT_EQ(fcall.getIdentifier(), "sin");
    EXPECT_EQ(fcall.getArgCount(), 1);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), -0.0625f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "-.0625");
    EXPECT_EQ(fcall.getArg(1), nullptr);
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_atan2) {
    const FunctionCall fcall("atan2(-.0625, +8.375)");
    EXPECT_EQ(fcall.getIdentifier(), "atan2");
    EXPECT_EQ(fcall.getArgCount(), 2);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), -0.0625f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "-.0625");
    ASSERT_NE(fcall.getArg(1), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(1)), +8.375f);
    EXPECT_EQ((Substring)(*fcall.getArg(1)), "+8.375");
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_digital_write) {
    const FunctionCall fcall("digitalWrite(13, 1)");
    EXPECT_EQ(fcall.getIdentifier(), "digitalWrite");
    EXPECT_EQ(fcall.getArgCount(), 2);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), 13);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "13");
    ASSERT_NE(fcall.getArg(1), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(1)), 1);
    EXPECT_EQ((Substring)(*fcall.getArg(1)), "1");
    EXPECT_EQ(fcall.getArg(2), nullptr);
    EXPECT_EQ(fcall.getArg(3), nullptr);
    EXPECT_EQ(fcall.getArg(4), nullptr);
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_baro) {
    const FunctionCall fcall("  qm.baro     (  +.25 ,  -3.125   , .875  , 0x818   , -.5   )   ");
    EXPECT_EQ(fcall.getIdentifier(), "qm.baro");
    EXPECT_EQ(fcall.getArgCount(), 5);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), 0.25f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "+.25");
    ASSERT_NE(fcall.getArg(1), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(1)), -3.125f);
    EXPECT_EQ((Substring)(*fcall.getArg(1)), "-3.125");
    ASSERT_NE(fcall.getArg(2), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(2)), 0.875f);
    EXPECT_EQ((Substring)(*fcall.getArg(2)), ".875");
    ASSERT_NE(fcall.getArg(3), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(3)), 0x818);
    EXPECT_EQ((Substring)(*fcall.getArg(3)), "0x818");
    ASSERT_NE(fcall.getArg(4), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(4)), -0.5f);
    EXPECT_EQ((Substring)(*fcall.getArg(4)), "-.5");
    EXPECT_EQ(fcall.getArg(5), nullptr);
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

TEST_F(FunctionCallTest, init_with_baro_and_constants) {
    const FunctionCall fcall("  qm.baro     (  +.25 ,  -3.125   , .875  , HIGH-1.8356   , -.5qwer   ,  0x818    )   ");
    EXPECT_EQ(fcall.getIdentifier(), "qm.baro");
    EXPECT_EQ(fcall.getArgCount(), 6);
    ASSERT_NE(fcall.getArg(0), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(0)), 0.25f);
    EXPECT_EQ((Substring)(*fcall.getArg(0)), "+.25");
    ASSERT_NE(fcall.getArg(1), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(1)), -3.125f);
    EXPECT_EQ((Substring)(*fcall.getArg(1)), "-3.125");
    ASSERT_NE(fcall.getArg(2), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(2)), 0.875f);
    EXPECT_EQ((Substring)(*fcall.getArg(2)), ".875");
    ASSERT_NE(fcall.getArg(3), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(3)), 0.0f);
    EXPECT_EQ((Substring)(*fcall.getArg(3)), "HIGH-1.8356");
    ASSERT_NE(fcall.getArg(4), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(4)), -0.5f);
    EXPECT_EQ((Substring)(*fcall.getArg(4)), "-.5qwer");
    ASSERT_NE(fcall.getArg(5), nullptr);
    EXPECT_EQ((float)(*fcall.getArg(5)), 0x818);
    EXPECT_EQ((Substring)(*fcall.getArg(5)), "0x818");
    EXPECT_EQ(fcall.getArg(6), nullptr);
    EXPECT_EQ(fcall.getArg(7), nullptr);
    EXPECT_EQ(fcall.getArg(8), nullptr);
    EXPECT_EQ(fcall.getArg(9), nullptr);
}

}

