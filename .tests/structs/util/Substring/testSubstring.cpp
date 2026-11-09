/**
 * Unit tests for the substring class.
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

#include "../../../mem_leak.h"
#include "../../../printers.h"

#include "../../../../src/structs/util/Substring.h"

using ino_interpreter::structs::util::Substring;

class SubstringTest : public tests::mem_leak::MemoryLeakCheckedTest {};

#define ASSERT_STR_EQ_STR_ONLY(x,y) { \
    EXPECT_TRUE(x == y); \
    EXPECT_TRUE(x <= y); \
    EXPECT_TRUE(x >= y); \
    EXPECT_FALSE(x < y); \
    EXPECT_FALSE(x > y); \
}

#define ASSERT_STR_LT_STR_ONLY(x,y) { \
    EXPECT_FALSE(x == y); \
    EXPECT_TRUE(x <= y); \
    EXPECT_FALSE(x >= y); \
    EXPECT_TRUE(x < y); \
    EXPECT_FALSE(x > y); \
}

#define ASSERT_STR_GT_STR_ONLY(x,y) { \
    EXPECT_FALSE(x == y); \
    EXPECT_FALSE(x <= y); \
    EXPECT_TRUE(x >= y); \
    EXPECT_FALSE(x < y); \
    EXPECT_TRUE(x > y); \
}

#define ASSERT_STR_EQ_STR(x,y) { ASSERT_STR_EQ_STR_ONLY(x,y); ASSERT_STR_EQ_STR_ONLY(y,x); }
#define ASSERT_STR_LT_STR(x,y) { ASSERT_STR_LT_STR_ONLY(x,y); ASSERT_STR_GT_STR_ONLY(y,x); }
#define ASSERT_STR_GT_STR(x,y) { ASSERT_STR_LT_STR(y,x); }

TEST_F(SubstringTest, empty_testcase) {
}

namespace empty_constructor {

TEST_F(SubstringTest, empty_constructor_memory_leak) {
    const Substring str;
}

TEST_F(SubstringTest, empty_constructor_gives_empty_string) {
    const Substring str;
    EXPECT_TRUE(str.isEmpty());
}

TEST_F(SubstringTest, empty_constructor_gives_zero_length) {
    const Substring str;
    const size_t length = str.getLength();
    EXPECT_EQ(length, 0);
}

TEST_F(SubstringTest, empty_constructor_gives_null_char) {
    const Substring str;
    EXPECT_EQ(str[0], '\0');
    EXPECT_EQ(str[1], '\0');
    EXPECT_EQ(str[2], '\0');
    EXPECT_EQ(str[3], '\0');
    EXPECT_EQ(str[4], '\0');
    EXPECT_EQ(str[5], '\0');
    EXPECT_EQ(str[6], '\0');
    EXPECT_EQ(str[7], '\0');
    EXPECT_EQ(str[8], '\0');
    EXPECT_EQ(str[9], '\0');
}

TEST_F(SubstringTest, empty_constructor_copy_to_buffer_gives_empty_string) {
    const Substring str;
    char arr [32];
    str.copyTo(arr);
    EXPECT_EQ(arr[0], '\0');
}

TEST_F(SubstringTest, empty_constructor_substring_1_param_gives_empty_string) {
    const Substring str;
    const Substring substr = str.substring(1);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, empty_constructor_substring_with_0_length_gives_empty_string) {
    const Substring str;
    const Substring substr = str.substring(1, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, empty_constructor_substring_2_param_gives_empty_string) {
    const Substring str;
    const Substring substr = str.substring(1, 1);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, empty_constructor_remove_head_spaces_gives_empty_string) {
    const Substring str;
    const Substring substr = str.removeHeadSpaces();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, empty_constructor_remove_tail_spaces_gives_empty_string) {
    const Substring str;
    const Substring substr = str.removeTailSpaces();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, empty_constructor_trim_gives_empty_string) {
    const Substring str;
    const Substring substr = str.trim();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, empty_constructor_index_of_somechar_gives_length) {
    const Substring str;
    EXPECT_EQ(str.indexOf('a'), str.getLength());
}

TEST_F(SubstringTest, empty_constructor_last_index_of_somechar_gives_length) {
    const Substring str;
    EXPECT_EQ(str.lastIndexOf('a'), str.getLength());
}

TEST_F(SubstringTest, empty_constructor_count_somechar_gives_0) {
    const Substring str;
    EXPECT_EQ(str.count('a'), 0);
}

TEST_F(SubstringTest, empty_constructor_equals_empty_c_string) {
    const Substring str;
    EXPECT_EQ(str, "");
}

TEST_F(SubstringTest, empty_constructor_equals_empty_string) {
    const Substring str;
    ASSERT_STR_EQ_STR(str, Substring(""));
}

TEST_F(SubstringTest, empty_constructor_splits_to_empty_string) {
    const Substring str;
    Substring substrings [16];
    str.split('a', substrings);
    for (Substring &s : substrings) {
        EXPECT_TRUE(s.isEmpty());
        EXPECT_EQ(s.getLength(), 0);
        EXPECT_EQ(s, "");
    }
}

TEST_F(SubstringTest, empty_constructor_assigned_c_string) {
    Substring str;
    const Substring &ref = (str = "Hello, world!");
    EXPECT_EQ(&ref, &str);
    EXPECT_FALSE(str.isEmpty());
    EXPECT_EQ(str.getLength(), 13);
    EXPECT_EQ(str, "Hello, world!");
}

TEST_F(SubstringTest, empty_constructor_assigned_string) {
    Substring str;
    const Substring another_string("Hello, world!");
    const Substring &ref = (str = another_string);
    EXPECT_EQ(&ref, &str);
    EXPECT_FALSE(str.isEmpty());
    EXPECT_EQ(str.getLength(), 13);
    EXPECT_EQ(str, "Hello, world!");
}

}

namespace c_string_constructor {

TEST_F(SubstringTest, c_string_constructor_memory_leak) {
    const Substring str("Hello, world!");
}

TEST_F(SubstringTest, empty_c_string_constructor_gives_empty_string) {
    const Substring str("");
    EXPECT_TRUE(str.isEmpty());
}

TEST_F(SubstringTest, c_string_1_constructor_gives_non_empty_string) {
    const Substring str("a");
    EXPECT_FALSE(str.isEmpty());
}

TEST_F(SubstringTest, c_string_2_constructor_gives_non_empty_string) {
    const Substring str("aa");
    EXPECT_FALSE(str.isEmpty());
}

TEST_F(SubstringTest, c_string_3_constructor_gives_non_empty_string) {
    const Substring str("aaa");
    EXPECT_FALSE(str.isEmpty());
}

TEST_F(SubstringTest, c_string_4_constructor_gives_non_empty_string) {
    const Substring str("qwer");
    EXPECT_FALSE(str.isEmpty());
}

TEST_F(SubstringTest, c_string_5_constructor_gives_non_empty_string) {
    const Substring str("yuiop");
    EXPECT_FALSE(str.isEmpty());
}

TEST_F(SubstringTest, empty_c_str_constructor_gives_zero_length) {
    const Substring str("");
    const size_t length = str.getLength();
    EXPECT_EQ(length, 0);
}

TEST_F(SubstringTest, c_str_1_constructor_gives_1_length) {
    const Substring str("a");
    const size_t length = str.getLength();
    EXPECT_EQ(length, 1);
}

TEST_F(SubstringTest, c_str_2_constructor_gives_2_length) {
    const Substring str("aa");
    const size_t length = str.getLength();
    EXPECT_EQ(length, 2);
}

TEST_F(SubstringTest, c_str_3_constructor_gives_3_length) {
    const Substring str("aaa");
    const size_t length = str.getLength();
    EXPECT_EQ(length, 3);
}

TEST_F(SubstringTest, c_str_4_constructor_gives_4_length) {
    const Substring str("qwer");
    const size_t length = str.getLength();
    EXPECT_EQ(length, 4);
}

TEST_F(SubstringTest, c_str_5_constructor_gives_5_length) {
    const Substring str("yuiop");
    const size_t length = str.getLength();
    EXPECT_EQ(length, 5);
}

TEST_F(SubstringTest, empty_c_str_constructor_gives_null_char) {
    const Substring str("");
    EXPECT_EQ(str[0], '\0');
    EXPECT_EQ(str[1], '\0');
    EXPECT_EQ(str[2], '\0');
    EXPECT_EQ(str[3], '\0');
    EXPECT_EQ(str[4], '\0');
    EXPECT_EQ(str[5], '\0');
    EXPECT_EQ(str[6], '\0');
    EXPECT_EQ(str[7], '\0');
    EXPECT_EQ(str[8], '\0');
    EXPECT_EQ(str[9], '\0');
}

TEST_F(SubstringTest, c_str_1_constructor_gives_corresponding_chars) {
    const Substring str("a");
    EXPECT_EQ(str[0], 'a');
    EXPECT_EQ(str[1], '\0');
    EXPECT_EQ(str[2], '\0');
    EXPECT_EQ(str[3], '\0');
    EXPECT_EQ(str[4], '\0');
    EXPECT_EQ(str[5], '\0');
    EXPECT_EQ(str[6], '\0');
    EXPECT_EQ(str[7], '\0');
    EXPECT_EQ(str[8], '\0');
    EXPECT_EQ(str[9], '\0');
}

TEST_F(SubstringTest, c_str_2_constructor_gives_corresponding_chars) {
    const Substring str("aa");
    EXPECT_EQ(str[0], 'a');
    EXPECT_EQ(str[1], 'a');
    EXPECT_EQ(str[2], '\0');
    EXPECT_EQ(str[3], '\0');
    EXPECT_EQ(str[4], '\0');
    EXPECT_EQ(str[5], '\0');
    EXPECT_EQ(str[6], '\0');
    EXPECT_EQ(str[7], '\0');
    EXPECT_EQ(str[8], '\0');
    EXPECT_EQ(str[9], '\0');
}

TEST_F(SubstringTest, c_str_3_constructor_gives_corresponding_chars) {
    const Substring str("aaa");
    EXPECT_EQ(str[0], 'a');
    EXPECT_EQ(str[1], 'a');
    EXPECT_EQ(str[2], 'a');
    EXPECT_EQ(str[3], '\0');
    EXPECT_EQ(str[4], '\0');
    EXPECT_EQ(str[5], '\0');
    EXPECT_EQ(str[6], '\0');
    EXPECT_EQ(str[7], '\0');
    EXPECT_EQ(str[8], '\0');
    EXPECT_EQ(str[9], '\0');
}

TEST_F(SubstringTest, c_str_4_constructor_gives_corresponding_chars) {
    const Substring str("qwer");
    EXPECT_EQ(str[0], 'q');
    EXPECT_EQ(str[1], 'w');
    EXPECT_EQ(str[2], 'e');
    EXPECT_EQ(str[3], 'r');
    EXPECT_EQ(str[4], '\0');
    EXPECT_EQ(str[5], '\0');
    EXPECT_EQ(str[6], '\0');
    EXPECT_EQ(str[7], '\0');
    EXPECT_EQ(str[8], '\0');
    EXPECT_EQ(str[9], '\0');
}

TEST_F(SubstringTest, c_str_5_constructor_gives_corresponding_chars) {
    const Substring str("yuiop");
    EXPECT_EQ(str[0], 'y');
    EXPECT_EQ(str[1], 'u');
    EXPECT_EQ(str[2], 'i');
    EXPECT_EQ(str[3], 'o');
    EXPECT_EQ(str[4], 'p');
    EXPECT_EQ(str[5], '\0');
    EXPECT_EQ(str[6], '\0');
    EXPECT_EQ(str[7], '\0');
    EXPECT_EQ(str[8], '\0');
    EXPECT_EQ(str[9], '\0');
}

TEST_F(SubstringTest, empty_c_str_constructor_copy_to_buffer_gives_empty_string) {
    const Substring str("");
    char arr [32];
    str.copyTo(arr);
    EXPECT_STREQ(arr, "");
}

TEST_F(SubstringTest, c_str_1_constructor_copy_to_buffer_gives_corresponding_string) {
    const Substring str("a");
    char arr [32];
    str.copyTo(arr);
    EXPECT_STREQ(arr, "a");
}

TEST_F(SubstringTest, c_str_2_constructor_copy_to_buffer_gives_corresponding_string) {
    const Substring str("aa");
    char arr [32];
    str.copyTo(arr);
    EXPECT_STREQ(arr, "aa");
}

TEST_F(SubstringTest, c_str_3_constructor_copy_to_buffer_gives_corresponding_string) {
    const Substring str("aaa");
    char arr [32];
    str.copyTo(arr);
    EXPECT_STREQ(arr, "aaa");
}

TEST_F(SubstringTest, c_str_4_constructor_copy_to_buffer_gives_corresponding_string) {
    const Substring str("qwer");
    char arr [32];
    str.copyTo(arr);
    EXPECT_STREQ(arr, "qwer");
}

TEST_F(SubstringTest, c_str_5_constructor_copy_to_buffer_gives_corresponding_string) {
    const Substring str("yuiop");
    char arr [32];
    str.copyTo(arr);
    EXPECT_STREQ(arr, "yuiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_remove_head_1_char) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "uiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_remove_head_2_chars) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "iop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_remove_head_3_chars) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "op");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_remove_head_4_chars) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_remove_head_5_chars) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_remove_head_6_chars) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_remove_head_7_chars) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_0_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_1_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_2_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_3_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_4_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_5_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_6_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_with_7_offset_0_length_gives_empty_string) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 0);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "y");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "yu");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 3);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "yui");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 4);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "yuio");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 5);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 5);
    EXPECT_EQ(substr, "yuiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 6);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 5);
    EXPECT_EQ(substr, "yuiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 7);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 5);
    EXPECT_EQ(substr, "yuiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "u");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "ui");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 3);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "uio");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 4);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "uiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 5);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "uiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 6);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "uiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 7);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "uiop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "i");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "io");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 3);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "iop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 4);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "iop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 5);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "iop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 6);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "iop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 7);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "iop");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_3_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "o");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_3_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "op");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_3_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 3);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "op");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_3_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 4);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "op");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_3_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 5);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "op");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_3_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 6);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "op");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_3_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 7);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "op");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_4_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_4_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_4_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 3);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_4_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 4);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_4_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 5);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_4_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 6);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_4_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 7);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "p");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_5_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 1);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_5_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 2);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_5_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 3);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_5_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 4);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_5_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 5);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_5_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 6);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_5_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 7);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 1);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 2);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 3);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 4);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 5);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 6);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 7);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_7_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 1);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_7_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 2);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_7_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 3);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_7_4) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 4);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_7_5) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 5);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_7_6) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 6);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_7_7) {
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 7);
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_substring_0_3) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1).substring(0, 3);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "uio");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_4_substring_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 4).substring(1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 3);
    EXPECT_EQ(substr, "uio");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_2_substring_0_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(2).substring(0, 2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "io");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_substring_1_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1).substring(1, 2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "io");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_0_4_substring_2) {
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 4).substring(2);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "io");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_1_3_substring_1) {
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 3).substring(1);
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 2);
    EXPECT_EQ(substr, "io");
}

TEST_F(SubstringTest, c_str_5_constructor_substring_6_12_substring_3_5_substring_4_8) {
    const Substring str("abcdefghijklmnopqrstuvwxyz");
    const Substring substr = str
        .substring(6, 12)  // "ghijklmnopqr"
        .substring(3, 5)   // "jklmn"
        .substring(4, 8);  // "n"
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, "n");
}

TEST_F(SubstringTest, c_str_constructor_remove_head_spaces_gives_corresponding_string_1) {
    const Substring str("   lmoi");
    const Substring substr = str.removeHeadSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_remove_head_spaces_gives_corresponding_string_2) {
    const Substring str("   asdf qwer  tuiop   ");
    const Substring substr = str.removeHeadSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 19);
    EXPECT_EQ(substr, "asdf qwer  tuiop   ");
}

TEST_F(SubstringTest, c_str_constructor_remove_head_spaces_gives_corresponding_string_3) {
    const Substring str("lmoi");
    const Substring substr = str.removeHeadSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_remove_head_spaces_gives_corresponding_string_4) {
    const Substring str("asdf qwer  tuiop   ");
    const Substring substr = str.removeHeadSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 19);
    EXPECT_EQ(substr, "asdf qwer  tuiop   ");
}

TEST_F(SubstringTest, c_str_constructor_remove_head_spaces_gives_corresponding_string_5) {
    const Substring str(" ");
    const Substring substr = str.removeHeadSpaces();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_constructor_remove_head_spaces_gives_corresponding_string_6) {
    const Substring str("     ");
    const Substring substr = str.removeHeadSpaces();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_constructor_remove_tail_spaces_gives_corresponding_string_1) {
    const Substring str("lmoi   ");
    const Substring substr = str.removeTailSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_remove_tail_spaces_gives_corresponding_string_2) {
    const Substring str("   asdf qwer  tuiop   ");
    const Substring substr = str.removeTailSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 19);
    EXPECT_EQ(substr, "   asdf qwer  tuiop");
}

TEST_F(SubstringTest, c_str_constructor_remove_tail_spaces_gives_corresponding_string_3) {
    const Substring str("lmoi");
    const Substring substr = str.removeTailSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_remove_tail_spaces_gives_corresponding_string_4) {
    const Substring str("   asdf qwer  tuiop");
    const Substring substr = str.removeTailSpaces();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 19);
    EXPECT_EQ(substr, "   asdf qwer  tuiop");
}

TEST_F(SubstringTest, c_str_constructor_remove_tail_spaces_gives_corresponding_string_5) {
    const Substring str(" ");
    const Substring substr = str.removeTailSpaces();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_constructor_remove_tail_spaces_gives_corresponding_string_6) {
    const Substring str("     ");
    const Substring substr = str.removeTailSpaces();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_1) {
    const Substring str("   lmoi   ");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_2) {
    const Substring str("   lmoi");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_3) {
    const Substring str("lmoi   ");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_4) {
    const Substring str("lmoi");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "lmoi");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_5) {
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 16);
    EXPECT_EQ(substr, "asdf qwer  tuiop");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_6) {
    const Substring str("asdf qwer  tuiop    ");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 16);
    EXPECT_EQ(substr, "asdf qwer  tuiop");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_7) {
    const Substring str("  asdf qwer  tuiop");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 16);
    EXPECT_EQ(substr, "asdf qwer  tuiop");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_8) {
    const Substring str("asdf qwer  tuiop");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 16);
    EXPECT_EQ(substr, "asdf qwer  tuiop");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_9) {
    const Substring str(" ");
    const Substring substr = str.trim();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_10) {
    const Substring str("     ");
    const Substring substr = str.trim();
    EXPECT_TRUE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 0);
    EXPECT_EQ(substr, "");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_11) {
    const Substring str(" ; ");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, ";");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_12) {
    const Substring str(", ");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, ",");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_13) {
    const Substring str(" ,");
    const Substring substr = str.trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 1);
    EXPECT_EQ(substr, ",");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_14) {
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.substring(0, 7).trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "asdf");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_15) {
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.substring(6, 7).trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 4);
    EXPECT_EQ(substr, "qwer");
}

TEST_F(SubstringTest, c_str_constructor_trim_gives_corresponding_string_16) {
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.substring(11, 11).trim();
    EXPECT_FALSE(substr.isEmpty());
    EXPECT_EQ(substr.getLength(), 5);
    EXPECT_EQ(substr, "tuiop");
}

TEST_F(SubstringTest, c_str_constructor_index_of_first_char_gives_0) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.indexOf('a'), 0);
}

TEST_F(SubstringTest, c_str_constructor_index_of_first_char_recurring_gives_0) {
    const Substring str("abcdefgabcde");
    EXPECT_EQ(str.indexOf('a'), 0);
}

TEST_F(SubstringTest, c_str_constructor_index_of_second_char_recurring_gives_1) {
    const Substring str("abcdefgabcde");
    EXPECT_EQ(str.indexOf('b'), 1);
}

TEST_F(SubstringTest, c_str_constructor_index_of_middle_char_gives_index) {
    const Substring str("abcdefgabcde");
    EXPECT_EQ(str.indexOf('f'), 5);
}

TEST_F(SubstringTest, c_str_constructor_index_of_second_last_char_gives_second_last_index) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.indexOf('f'), 5);
}

TEST_F(SubstringTest, c_str_constructor_index_of_last_char_gives_last_index) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.indexOf('g'), 6);
}

TEST_F(SubstringTest, c_str_constructor_index_of_nonexisting_char_gives_length) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.indexOf('x'), 7);
    EXPECT_EQ(str.getLength(), 7);
}

TEST_F(SubstringTest, c_str_constructor_last_index_of_first_char_gives_0) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.lastIndexOf('a'), 0);
}

TEST_F(SubstringTest, c_str_constructor_last_index_of_first_char_recurring_gives_middle_index) {
    const Substring str("abcdefgabcde");
    EXPECT_EQ(str.lastIndexOf('a'), 7);
}

TEST_F(SubstringTest, c_str_constructor_last_index_of_second_char_recurring_gives_middle_index) {
    const Substring str("abcdefgabcde");
    EXPECT_EQ(str.lastIndexOf('b'), 8);
}

TEST_F(SubstringTest, c_str_constructor_last_index_of_middle_char_gives_index) {
    const Substring str("abcdefgabcde");
    EXPECT_EQ(str.lastIndexOf('f'), 5);
}

TEST_F(SubstringTest, c_str_constructor_last_index_of_second_last_char_gives_second_last_index) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.lastIndexOf('f'), 5);
}

TEST_F(SubstringTest, c_str_constructor_last_index_of_last_char_gives_last_index) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.lastIndexOf('g'), 6);
}

TEST_F(SubstringTest, c_str_constructor_last_index_of_nonexisting_char_gives_length) {
    const Substring str("abcdefg");
    EXPECT_EQ(str.lastIndexOf('x'), 7);
    EXPECT_EQ(str.getLength(), 7);
}

TEST_F(SubstringTest, empty_c_str_constructor_count_somechar_gives_0) {
    const Substring str("");
    EXPECT_EQ(str.count('a'), 0);
}

TEST_F(SubstringTest, c_str_constructor_count_gives_1) {
    const Substring str("a");
    EXPECT_EQ(str.count('a'), 1);
}

TEST_F(SubstringTest, c_str_constructor_count_gives_2) {
    const Substring str("aa");
    EXPECT_EQ(str.count('a'), 2);
}

TEST_F(SubstringTest, c_str_constructor_count_gives_3) {
    const Substring str("aaa");
    EXPECT_EQ(str.count('a'), 3);
}

TEST_F(SubstringTest, c_str_constructor_count_gives_4) {
    const Substring str("aaaa");
    EXPECT_EQ(str.count('a'), 4);
}

TEST_F(SubstringTest, c_str_constructor_count_gives_5) {
    const Substring str("aaaaa");
    EXPECT_EQ(str.count('a'), 5);
}

TEST_F(SubstringTest, c_str_constructor_count_randomstr_gives_1) {
    const Substring str("rqew0y81342itapwer8not2b3gon");
    EXPECT_EQ(str.count('a'), 1);
}

TEST_F(SubstringTest, c_str_constructor_count_randomstr_gives_2) {
    const Substring str("rqew0y81342itapwer8nota2b3gon");
    EXPECT_EQ(str.count('a'), 2);
}

TEST_F(SubstringTest, c_str_constructor_count_randomstr_gives_3) {
    const Substring str("rqeaw0y81342itapwer8nota2b3gon");
    EXPECT_EQ(str.count('a'), 3);
}

TEST_F(SubstringTest, c_str_constructor_count_randomstr_gives_4) {
    const Substring str("rqewa0y81342itapwer8nota2b3agon");
    EXPECT_EQ(str.count('a'), 4);
}

TEST_F(SubstringTest, c_str_constructor_count_randomstr_gives_5) {
    const Substring str("rqewa0y81342itapwer8notaa2b3agon");
    EXPECT_EQ(str.count('a'), 5);
}

TEST_F(SubstringTest, empty_c_str_constructor_equals_empty_c_string) {
    const Substring str("");
    EXPECT_EQ(str, "");
}

TEST_F(SubstringTest, c_str_constructor_equals_c_string) {
    const Substring str("Hello, world!");
    EXPECT_EQ(str, "Hello, world!");
}

TEST_F(SubstringTest, empty_c_str_constructor_equals_empty_string) {
    const Substring str("");
    EXPECT_EQ(str, Substring(""));
}

TEST_F(SubstringTest, c_str_constructor_equals_string) {
    const Substring str("Hello, world!");
    ASSERT_STR_EQ_STR(str, Substring("Hello, world!"));
}

TEST_F(SubstringTest, c_str_constructor_splits_to_strings_0) {
    const Substring str("asdf,qwergui,zx");
    Substring substrings [16];
    str.split('#', substrings);
    EXPECT_EQ(substrings[0], "asdf,qwergui,zx");
    EXPECT_EQ(substrings[1], "");
    EXPECT_EQ(substrings[2], "");
    EXPECT_EQ(substrings[3], "");
    EXPECT_EQ(substrings[4], "");
    EXPECT_EQ(substrings[5], "");
    EXPECT_EQ(substrings[6], "");
    EXPECT_EQ(substrings[7], "");
}

TEST_F(SubstringTest, c_str_constructor_splits_to_strings_1) {
    const Substring str("asdf,qwergui,zx");
    Substring substrings [16];
    str.split(',', substrings);
    EXPECT_EQ(substrings[0], "asdf");
    EXPECT_EQ(substrings[1], "qwergui");
    EXPECT_EQ(substrings[2], "zx");
    EXPECT_EQ(substrings[3], "");
    EXPECT_EQ(substrings[4], "");
    EXPECT_EQ(substrings[5], "");
    EXPECT_EQ(substrings[6], "");
    EXPECT_EQ(substrings[7], "");
}

TEST_F(SubstringTest, c_str_constructor_splits_to_strings_2) {
    const Substring str(",asdf,qwergui,zx");
    Substring substrings [16];
    str.split(',', substrings);
    EXPECT_EQ(substrings[0], "");
    EXPECT_EQ(substrings[1], "asdf");
    EXPECT_EQ(substrings[2], "qwergui");
    EXPECT_EQ(substrings[3], "zx");
    EXPECT_EQ(substrings[4], "");
    EXPECT_EQ(substrings[5], "");
    EXPECT_EQ(substrings[6], "");
    EXPECT_EQ(substrings[7], "");
}

TEST_F(SubstringTest, c_str_constructor_splits_to_strings_3) {
    const Substring str("asdf,qwergui,zx,");
    Substring substrings [16];
    str.split(',', substrings);
    EXPECT_EQ(substrings[0], "asdf");
    EXPECT_EQ(substrings[1], "qwergui");
    EXPECT_EQ(substrings[2], "zx");
    EXPECT_EQ(substrings[3], "");
    EXPECT_EQ(substrings[4], "");
    EXPECT_EQ(substrings[5], "");
    EXPECT_EQ(substrings[6], "");
    EXPECT_EQ(substrings[7], "");
}

TEST_F(SubstringTest, c_str_constructor_splits_to_strings_4) {
    const Substring str(";digitalWrite(35, HIGH);analogRead(A3);;");
    Substring substrings [16];
    str.split(';', substrings);
    EXPECT_EQ(substrings[0], "");
    EXPECT_EQ(substrings[1], "digitalWrite(35, HIGH)");
    EXPECT_EQ(substrings[2], "analogRead(A3)");
    EXPECT_EQ(substrings[3], "");
    EXPECT_EQ(substrings[4], "");
    EXPECT_EQ(substrings[5], "");
    EXPECT_EQ(substrings[6], "");
    EXPECT_EQ(substrings[7], "");
}

TEST_F(SubstringTest, c_str_constructor_splits_to_strings_5) {
    const Substring str("a,b,c,d,e");
    Substring substrings [16];
    str.split(',', substrings);
    EXPECT_EQ(substrings[0], "a");
    EXPECT_EQ(substrings[1], "b");
    EXPECT_EQ(substrings[2], "c");
    EXPECT_EQ(substrings[3], "d");
    EXPECT_EQ(substrings[4], "e");
    EXPECT_EQ(substrings[5], "");
    EXPECT_EQ(substrings[6], "");
    EXPECT_EQ(substrings[7], "");
}

TEST_F(SubstringTest, c_str_constructor_assigned_c_string) {
    Substring str("Greetings from robot.");
    EXPECT_FALSE(str.isEmpty());
    EXPECT_EQ(str.getLength(), 21);
    EXPECT_EQ(str, "Greetings from robot.");
    const Substring &ref = (str = "Hello, world!");
    EXPECT_EQ(&ref, &str);
    EXPECT_FALSE(str.isEmpty());
    EXPECT_EQ(str.getLength(), 13);
    EXPECT_EQ(str, "Hello, world!");
}

TEST_F(SubstringTest, c_str_constructor_assigned_string) {
    Substring str("Greetings from robot.");
    EXPECT_FALSE(str.isEmpty());
    EXPECT_EQ(str.getLength(), 21);
    EXPECT_EQ(str, "Greetings from robot.");
    const Substring another_string("Hello, world!");
    const Substring &ref = (str = another_string);
    EXPECT_EQ(&ref, &str);
    EXPECT_FALSE(str.isEmpty());
    EXPECT_EQ(str.getLength(), 13);
    EXPECT_EQ(str, "Hello, world!");
}

}

namespace lexicographical_comparison {

TEST_F(SubstringTest, empty_str_vs_empty_str) {
    Substring str1("");
    Substring str2("");
    ASSERT_STR_EQ_STR(str1, str2);
}

TEST_F(SubstringTest, empty_str_vs_single_char_str) {
    Substring str1("");
    Substring str2("a");
    ASSERT_STR_LT_STR(str1, str2);
}

TEST_F(SubstringTest, single_char_str_vs_other_single_char_str) {
    Substring str1("a");
    Substring str2("b");
    ASSERT_STR_LT_STR(str1, str2);
}

TEST_F(SubstringTest, lower_single_char_str_vs_upper_single_char_str) {
    Substring str1("A");
    Substring str2("a");
    ASSERT_STR_LT_STR(str1, str2);
}

TEST_F(SubstringTest, str_vs_substr) {
    Substring str1("abc");
    Substring str2("abcd");
    ASSERT_STR_LT_STR(str1, str2);
}

TEST_F(SubstringTest, parent_member_str_vs_child_member_str) {
    Substring str1("top.yhchoi.jm9.xrcu");
    Substring str2("top.yhchoi.jm9.xrcu.hardware");
    ASSERT_STR_LT_STR(str1, str2);
}

TEST_F(SubstringTest, str_vs_same_str) {
    Substring str1("top.yhchoi.jm9.xrcu.hardware");
    Substring str2("top.yhchoi.jm9.xrcu.hardware");
    ASSERT_STR_EQ_STR(str1, str2);
}

}

