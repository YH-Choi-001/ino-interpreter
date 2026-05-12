#include "../../../test.h"

#include "../../../../src/structs/util/Substring.h"

using ino_interpreter::structs::util::Substring;

std::ostream &operator<<(std::ostream &os, const Substring &str) {
    const size_t len = str.getLength();
    for (size_t i = 0; i < len; i++) {
        os << str[i];
    }
    return os;
}

#define ASSERT_STR_EQ_STR_ONLY(x,y) { \
    ASSERT_TRUE(x == y); \
    ASSERT_TRUE(x <= y); \
    ASSERT_TRUE(x >= y); \
    ASSERT_FALSE(x < y); \
    ASSERT_FALSE(x > y); \
}

#define ASSERT_STR_LT_STR_ONLY(x,y) { \
    ASSERT_FALSE(x == y); \
    ASSERT_TRUE(x <= y); \
    ASSERT_FALSE(x >= y); \
    ASSERT_TRUE(x < y); \
    ASSERT_FALSE(x > y); \
}

#define ASSERT_STR_GT_STR_ONLY(x,y) { \
    ASSERT_FALSE(x == y); \
    ASSERT_FALSE(x <= y); \
    ASSERT_TRUE(x >= y); \
    ASSERT_FALSE(x < y); \
    ASSERT_TRUE(x > y); \
}

#define ASSERT_STR_EQ_STR(x,y) { ASSERT_STR_EQ_STR_ONLY(x,y); ASSERT_STR_EQ_STR_ONLY(y,x); }
#define ASSERT_STR_LT_STR(x,y) { ASSERT_STR_LT_STR_ONLY(x,y); ASSERT_STR_GT_STR_ONLY(y,x); }
#define ASSERT_STR_GT_STR(x,y) { ASSERT_STR_LT_STR(y,x); }

TEST_BEGIN(empty_testcase)
    result.passed = true;
TEST_END()

namespace empty_constructor {

TEST_BEGIN(empty_constructor_memory_leak)
    result.passed = true;
    const Substring str;
TEST_END()

TEST_BEGIN(empty_constructor_gives_empty_string)
    const Substring str;
    ASSERT_TRUE(str.isEmpty());
TEST_END()

TEST_BEGIN(empty_constructor_gives_zero_length)
    const Substring str;
    const size_t length = str.getLength();
    ASSERT_EQUALS(length, 0);
TEST_END()

TEST_BEGIN(empty_constructor_gives_null_char)
    const Substring str;
    ASSERT_EQUALS(str[0], '\0');
    ASSERT_EQUALS(str[1], '\0');
    ASSERT_EQUALS(str[2], '\0');
    ASSERT_EQUALS(str[3], '\0');
    ASSERT_EQUALS(str[4], '\0');
    ASSERT_EQUALS(str[5], '\0');
    ASSERT_EQUALS(str[6], '\0');
    ASSERT_EQUALS(str[7], '\0');
    ASSERT_EQUALS(str[8], '\0');
    ASSERT_EQUALS(str[9], '\0');
TEST_END()

TEST_BEGIN(empty_constructor_copy_to_buffer_gives_empty_string)
    const Substring str;
    char arr [32];
    str.copyTo(arr);
    ASSERT_EQUALS(arr[0], '\0');
TEST_END()

TEST_BEGIN(empty_constructor_substring_1_param_gives_empty_string)
    const Substring str;
    const Substring substr = str.substring(1);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(empty_constructor_substring_with_0_length_gives_empty_string)
    const Substring str;
    const Substring substr = str.substring(1, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(empty_constructor_substring_2_param_gives_empty_string)
    const Substring str;
    const Substring substr = str.substring(1, 1);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(empty_constructor_remove_head_spaces_gives_empty_string)
    const Substring str;
    const Substring substr = str.removeHeadSpaces();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(empty_constructor_remove_tail_spaces_gives_empty_string)
    const Substring str;
    const Substring substr = str.removeTailSpaces();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(empty_constructor_trim_gives_empty_string)
    const Substring str;
    const Substring substr = str.trim();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(empty_constructor_index_of_somechar_gives_length)
    const Substring str;
    ASSERT_EQUALS(str.indexOf('a'), str.getLength());
TEST_END()

TEST_BEGIN(empty_constructor_last_index_of_somechar_gives_length)
    const Substring str;
    ASSERT_EQUALS(str.lastIndexOf('a'), str.getLength());
TEST_END()

TEST_BEGIN(empty_constructor_count_somechar_gives_0)
    const Substring str;
    ASSERT_EQUALS(str.count('a'), 0);
TEST_END()

TEST_BEGIN(empty_constructor_equals_empty_c_string)
    const Substring str;
    ASSERT_EQUALS(str, "");
TEST_END()

TEST_BEGIN(empty_constructor_equals_empty_string)
    const Substring str;
    ASSERT_STR_EQ_STR(str, Substring(""));
TEST_END()

TEST_BEGIN(empty_constructor_splits_to_empty_string)
    const Substring str;
    Substring substrings [16];
    str.split('a', substrings);
    for (Substring &s : substrings) {
        ASSERT_TRUE(s.isEmpty());
        ASSERT_EQUALS(s.getLength(), 0);
        ASSERT_EQUALS(s, "");
    }
TEST_END()

TEST_BEGIN(empty_constructor_assigned_c_string)
    Substring str;
    const Substring &ref = (str = "Hello, world!");
    ASSERT_EQUALS(&ref, &str);
    ASSERT_FALSE(str.isEmpty());
    ASSERT_EQUALS(str.getLength(), 13);
    ASSERT_EQUALS(str, "Hello, world!");
TEST_END()

TEST_BEGIN(empty_constructor_assigned_string)
    Substring str;
    const Substring another_string("Hello, world!");
    const Substring &ref = (str = another_string);
    ASSERT_EQUALS(&ref, &str);
    ASSERT_FALSE(str.isEmpty());
    ASSERT_EQUALS(str.getLength(), 13);
    ASSERT_EQUALS(str, "Hello, world!");
TEST_END()

}

namespace c_string_constructor {

TEST_BEGIN(c_string_constructor_memory_leak)
    result.passed = true;
    const Substring str("Hello, world!");
TEST_END()

TEST_BEGIN(empty_c_string_constructor_gives_empty_string)
    const Substring str("");
    ASSERT_TRUE(str.isEmpty());
TEST_END()

TEST_BEGIN(c_string_1_constructor_gives_non_empty_string)
    const Substring str("a");
    ASSERT_FALSE(str.isEmpty());
TEST_END()

TEST_BEGIN(c_string_2_constructor_gives_non_empty_string)
    const Substring str("aa");
    ASSERT_FALSE(str.isEmpty());
TEST_END()

TEST_BEGIN(c_string_3_constructor_gives_non_empty_string)
    const Substring str("aaa");
    ASSERT_FALSE(str.isEmpty());
TEST_END()

TEST_BEGIN(c_string_4_constructor_gives_non_empty_string)
    const Substring str("qwer");
    ASSERT_FALSE(str.isEmpty());
TEST_END()

TEST_BEGIN(c_string_5_constructor_gives_non_empty_string)
    const Substring str("yuiop");
    ASSERT_FALSE(str.isEmpty());
TEST_END()

TEST_BEGIN(empty_c_str_constructor_gives_zero_length)
    const Substring str("");
    const size_t length = str.getLength();
    ASSERT_EQUALS(length, 0);
TEST_END()

TEST_BEGIN(c_str_1_constructor_gives_1_length)
    const Substring str("a");
    const size_t length = str.getLength();
    ASSERT_EQUALS(length, 1);
TEST_END()

TEST_BEGIN(c_str_2_constructor_gives_2_length)
    const Substring str("aa");
    const size_t length = str.getLength();
    ASSERT_EQUALS(length, 2);
TEST_END()

TEST_BEGIN(c_str_3_constructor_gives_3_length)
    const Substring str("aaa");
    const size_t length = str.getLength();
    ASSERT_EQUALS(length, 3);
TEST_END()

TEST_BEGIN(c_str_4_constructor_gives_4_length)
    const Substring str("qwer");
    const size_t length = str.getLength();
    ASSERT_EQUALS(length, 4);
TEST_END()

TEST_BEGIN(c_str_5_constructor_gives_5_length)
    const Substring str("yuiop");
    const size_t length = str.getLength();
    ASSERT_EQUALS(length, 5);
TEST_END()

TEST_BEGIN(empty_c_str_constructor_gives_null_char)
    const Substring str("");
    ASSERT_EQUALS(str[0], '\0');
    ASSERT_EQUALS(str[1], '\0');
    ASSERT_EQUALS(str[2], '\0');
    ASSERT_EQUALS(str[3], '\0');
    ASSERT_EQUALS(str[4], '\0');
    ASSERT_EQUALS(str[5], '\0');
    ASSERT_EQUALS(str[6], '\0');
    ASSERT_EQUALS(str[7], '\0');
    ASSERT_EQUALS(str[8], '\0');
    ASSERT_EQUALS(str[9], '\0');
TEST_END()

TEST_BEGIN(c_str_1_constructor_gives_corresponding_chars)
    const Substring str("a");
    ASSERT_EQUALS(str[0], 'a');
    ASSERT_EQUALS(str[1], '\0');
    ASSERT_EQUALS(str[2], '\0');
    ASSERT_EQUALS(str[3], '\0');
    ASSERT_EQUALS(str[4], '\0');
    ASSERT_EQUALS(str[5], '\0');
    ASSERT_EQUALS(str[6], '\0');
    ASSERT_EQUALS(str[7], '\0');
    ASSERT_EQUALS(str[8], '\0');
    ASSERT_EQUALS(str[9], '\0');
TEST_END()

TEST_BEGIN(c_str_2_constructor_gives_corresponding_chars)
    const Substring str("aa");
    ASSERT_EQUALS(str[0], 'a');
    ASSERT_EQUALS(str[1], 'a');
    ASSERT_EQUALS(str[2], '\0');
    ASSERT_EQUALS(str[3], '\0');
    ASSERT_EQUALS(str[4], '\0');
    ASSERT_EQUALS(str[5], '\0');
    ASSERT_EQUALS(str[6], '\0');
    ASSERT_EQUALS(str[7], '\0');
    ASSERT_EQUALS(str[8], '\0');
    ASSERT_EQUALS(str[9], '\0');
TEST_END()

TEST_BEGIN(c_str_3_constructor_gives_corresponding_chars)
    const Substring str("aaa");
    ASSERT_EQUALS(str[0], 'a');
    ASSERT_EQUALS(str[1], 'a');
    ASSERT_EQUALS(str[2], 'a');
    ASSERT_EQUALS(str[3], '\0');
    ASSERT_EQUALS(str[4], '\0');
    ASSERT_EQUALS(str[5], '\0');
    ASSERT_EQUALS(str[6], '\0');
    ASSERT_EQUALS(str[7], '\0');
    ASSERT_EQUALS(str[8], '\0');
    ASSERT_EQUALS(str[9], '\0');
TEST_END()

TEST_BEGIN(c_str_4_constructor_gives_corresponding_chars)
    const Substring str("qwer");
    ASSERT_EQUALS(str[0], 'q');
    ASSERT_EQUALS(str[1], 'w');
    ASSERT_EQUALS(str[2], 'e');
    ASSERT_EQUALS(str[3], 'r');
    ASSERT_EQUALS(str[4], '\0');
    ASSERT_EQUALS(str[5], '\0');
    ASSERT_EQUALS(str[6], '\0');
    ASSERT_EQUALS(str[7], '\0');
    ASSERT_EQUALS(str[8], '\0');
    ASSERT_EQUALS(str[9], '\0');
TEST_END()

TEST_BEGIN(c_str_5_constructor_gives_corresponding_chars)
    const Substring str("yuiop");
    ASSERT_EQUALS(str[0], 'y');
    ASSERT_EQUALS(str[1], 'u');
    ASSERT_EQUALS(str[2], 'i');
    ASSERT_EQUALS(str[3], 'o');
    ASSERT_EQUALS(str[4], 'p');
    ASSERT_EQUALS(str[5], '\0');
    ASSERT_EQUALS(str[6], '\0');
    ASSERT_EQUALS(str[7], '\0');
    ASSERT_EQUALS(str[8], '\0');
    ASSERT_EQUALS(str[9], '\0');
TEST_END()

TEST_BEGIN(empty_c_str_constructor_copy_to_buffer_gives_empty_string)
    const Substring str("");
    char arr [32];
    str.copyTo(arr);
    ASSERT_CSTR_EQUALS(arr, "");
TEST_END()

TEST_BEGIN(c_str_1_constructor_copy_to_buffer_gives_corresponding_string)
    const Substring str("a");
    char arr [32];
    str.copyTo(arr);
    ASSERT_CSTR_EQUALS(arr, "a");
TEST_END()

TEST_BEGIN(c_str_2_constructor_copy_to_buffer_gives_corresponding_string)
    const Substring str("aa");
    char arr [32];
    str.copyTo(arr);
    ASSERT_CSTR_EQUALS(arr, "aa");
TEST_END()

TEST_BEGIN(c_str_3_constructor_copy_to_buffer_gives_corresponding_string)
    const Substring str("aaa");
    char arr [32];
    str.copyTo(arr);
    ASSERT_CSTR_EQUALS(arr, "aaa");
TEST_END()

TEST_BEGIN(c_str_4_constructor_copy_to_buffer_gives_corresponding_string)
    const Substring str("qwer");
    char arr [32];
    str.copyTo(arr);
    ASSERT_CSTR_EQUALS(arr, "qwer");
TEST_END()

TEST_BEGIN(c_str_5_constructor_copy_to_buffer_gives_corresponding_string)
    const Substring str("yuiop");
    char arr [32];
    str.copyTo(arr);
    ASSERT_CSTR_EQUALS(arr, "yuiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_remove_head_1_char)
    const Substring str("yuiop");
    const Substring substr = str.substring(1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "uiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_remove_head_2_chars)
    const Substring str("yuiop");
    const Substring substr = str.substring(2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "iop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_remove_head_3_chars)
    const Substring str("yuiop");
    const Substring substr = str.substring(3);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "op");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_remove_head_4_chars)
    const Substring str("yuiop");
    const Substring substr = str.substring(4);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_remove_head_5_chars)
    const Substring str("yuiop");
    const Substring substr = str.substring(5);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_remove_head_6_chars)
    const Substring str("yuiop");
    const Substring substr = str.substring(6);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_remove_head_7_chars)
    const Substring str("yuiop");
    const Substring substr = str.substring(7);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_0_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_1_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_2_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_3_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_4_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_5_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_6_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_with_7_offset_0_length_gives_empty_string)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 0);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "y");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "yu");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 3);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "yui");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 4);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "yuio");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 5);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 5);
    ASSERT_EQUALS(substr, "yuiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 6);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 5);
    ASSERT_EQUALS(substr, "yuiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 7);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 5);
    ASSERT_EQUALS(substr, "yuiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "u");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "ui");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 3);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "uio");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 4);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "uiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 5);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "uiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 6);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "uiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 7);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "uiop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "i");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "io");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 3);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "iop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 4);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "iop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 5);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "iop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 6);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "iop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(2, 7);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "iop");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_3_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "o");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_3_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "op");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_3_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 3);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "op");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_3_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 4);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "op");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_3_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 5);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "op");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_3_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 6);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "op");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_3_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(3, 7);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "op");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_4_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_4_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_4_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 3);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_4_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 4);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_4_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 5);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_4_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 6);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_4_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(4, 7);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "p");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_5_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 1);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_5_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 2);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_5_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 3);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_5_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 4);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_5_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 5);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_5_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 6);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_5_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(5, 7);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 1);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 2);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 3);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 4);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 5);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 6);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(6, 7);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_7_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 1);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_7_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 2);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_7_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 3);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_7_4)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 4);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_7_5)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 5);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_7_6)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 6);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_7_7)
    const Substring str("yuiop");
    const Substring substr = str.substring(7, 7);
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_substring_0_3)
    const Substring str("yuiop");
    const Substring substr = str.substring(1).substring(0, 3);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "uio");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_4_substring_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 4).substring(1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 3);
    ASSERT_EQUALS(substr, "uio");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_2_substring_0_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(2).substring(0, 2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "io");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_substring_1_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(1).substring(1, 2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "io");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_0_4_substring_2)
    const Substring str("yuiop");
    const Substring substr = str.substring(0, 4).substring(2);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "io");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_1_3_substring_1)
    const Substring str("yuiop");
    const Substring substr = str.substring(1, 3).substring(1);
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 2);
    ASSERT_EQUALS(substr, "io");
TEST_END()

TEST_BEGIN(c_str_5_constructor_substring_6_12_substring_3_5_substring_4_8)
    const Substring str("abcdefghijklmnopqrstuvwxyz");
    const Substring substr = str
        .substring(6, 12)  // "ghijklmnopqr"
        .substring(3, 5)   // "jklmn"
        .substring(4, 8);  // "n"
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, "n");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_head_spaces_gives_corresponding_string_1)
    const Substring str("   lmoi");
    const Substring substr = str.removeHeadSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_head_spaces_gives_corresponding_string_2)
    const Substring str("   asdf qwer  tuiop   ");
    const Substring substr = str.removeHeadSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 19);
    ASSERT_EQUALS(substr, "asdf qwer  tuiop   ");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_head_spaces_gives_corresponding_string_3)
    const Substring str("lmoi");
    const Substring substr = str.removeHeadSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_head_spaces_gives_corresponding_string_4)
    const Substring str("asdf qwer  tuiop   ");
    const Substring substr = str.removeHeadSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 19);
    ASSERT_EQUALS(substr, "asdf qwer  tuiop   ");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_head_spaces_gives_corresponding_string_5)
    const Substring str(" ");
    const Substring substr = str.removeHeadSpaces();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_head_spaces_gives_corresponding_string_6)
    const Substring str("     ");
    const Substring substr = str.removeHeadSpaces();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_tail_spaces_gives_corresponding_string_1)
    const Substring str("lmoi   ");
    const Substring substr = str.removeTailSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_tail_spaces_gives_corresponding_string_2)
    const Substring str("   asdf qwer  tuiop   ");
    const Substring substr = str.removeTailSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 19);
    ASSERT_EQUALS(substr, "   asdf qwer  tuiop");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_tail_spaces_gives_corresponding_string_3)
    const Substring str("lmoi");
    const Substring substr = str.removeTailSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_tail_spaces_gives_corresponding_string_4)
    const Substring str("   asdf qwer  tuiop");
    const Substring substr = str.removeTailSpaces();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 19);
    ASSERT_EQUALS(substr, "   asdf qwer  tuiop");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_tail_spaces_gives_corresponding_string_5)
    const Substring str(" ");
    const Substring substr = str.removeTailSpaces();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_constructor_remove_tail_spaces_gives_corresponding_string_6)
    const Substring str("     ");
    const Substring substr = str.removeTailSpaces();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_1)
    const Substring str("   lmoi   ");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_2)
    const Substring str("   lmoi");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_3)
    const Substring str("lmoi   ");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_4)
    const Substring str("lmoi");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "lmoi");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_5)
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 16);
    ASSERT_EQUALS(substr, "asdf qwer  tuiop");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_6)
    const Substring str("asdf qwer  tuiop    ");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 16);
    ASSERT_EQUALS(substr, "asdf qwer  tuiop");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_7)
    const Substring str("  asdf qwer  tuiop");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 16);
    ASSERT_EQUALS(substr, "asdf qwer  tuiop");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_8)
    const Substring str("asdf qwer  tuiop");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 16);
    ASSERT_EQUALS(substr, "asdf qwer  tuiop");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_9)
    const Substring str(" ");
    const Substring substr = str.trim();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_10)
    const Substring str("     ");
    const Substring substr = str.trim();
    ASSERT_TRUE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 0);
    ASSERT_EQUALS(substr, "");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_11)
    const Substring str(" ; ");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, ";");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_12)
    const Substring str(", ");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, ",");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_13)
    const Substring str(" ,");
    const Substring substr = str.trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 1);
    ASSERT_EQUALS(substr, ",");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_14)
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.substring(0, 7).trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "asdf");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_15)
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.substring(6, 7).trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 4);
    ASSERT_EQUALS(substr, "qwer");
TEST_END()

TEST_BEGIN(c_str_constructor_trim_gives_corresponding_string_16)
    const Substring str("  asdf qwer  tuiop    ");
    const Substring substr = str.substring(11, 11).trim();
    ASSERT_FALSE(substr.isEmpty());
    ASSERT_EQUALS(substr.getLength(), 5);
    ASSERT_EQUALS(substr, "tuiop");
TEST_END()

TEST_BEGIN(c_str_constructor_index_of_first_char_gives_0)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.indexOf('a'), 0);
TEST_END()

TEST_BEGIN(c_str_constructor_index_of_first_char_recurring_gives_0)
    const Substring str("abcdefgabcde");
    ASSERT_EQUALS(str.indexOf('a'), 0);
TEST_END()

TEST_BEGIN(c_str_constructor_index_of_second_char_recurring_gives_1)
    const Substring str("abcdefgabcde");
    ASSERT_EQUALS(str.indexOf('b'), 1);
TEST_END()

TEST_BEGIN(c_str_constructor_index_of_middle_char_gives_index)
    const Substring str("abcdefgabcde");
    ASSERT_EQUALS(str.indexOf('f'), 5);
TEST_END()

TEST_BEGIN(c_str_constructor_index_of_second_last_char_gives_second_last_index)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.indexOf('f'), 5);
TEST_END()

TEST_BEGIN(c_str_constructor_index_of_last_char_gives_last_index)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.indexOf('g'), 6);
TEST_END()

TEST_BEGIN(c_str_constructor_index_of_nonexisting_char_gives_length)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.indexOf('x'), 7);
    ASSERT_EQUALS(str.getLength(), 7);
TEST_END()

TEST_BEGIN(c_str_constructor_last_index_of_first_char_gives_0)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.lastIndexOf('a'), 0);
TEST_END()

TEST_BEGIN(c_str_constructor_last_index_of_first_char_recurring_gives_middle_index)
    const Substring str("abcdefgabcde");
    ASSERT_EQUALS(str.lastIndexOf('a'), 7);
TEST_END()

TEST_BEGIN(c_str_constructor_last_index_of_second_char_recurring_gives_middle_index)
    const Substring str("abcdefgabcde");
    ASSERT_EQUALS(str.lastIndexOf('b'), 8);
TEST_END()

TEST_BEGIN(c_str_constructor_last_index_of_middle_char_gives_index)
    const Substring str("abcdefgabcde");
    ASSERT_EQUALS(str.lastIndexOf('f'), 5);
TEST_END()

TEST_BEGIN(c_str_constructor_last_index_of_second_last_char_gives_second_last_index)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.lastIndexOf('f'), 5);
TEST_END()

TEST_BEGIN(c_str_constructor_last_index_of_last_char_gives_last_index)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.lastIndexOf('g'), 6);
TEST_END()

TEST_BEGIN(c_str_constructor_last_index_of_nonexisting_char_gives_length)
    const Substring str("abcdefg");
    ASSERT_EQUALS(str.lastIndexOf('x'), 7);
    ASSERT_EQUALS(str.getLength(), 7);
TEST_END()

TEST_BEGIN(empty_c_str_constructor_count_somechar_gives_0)
    const Substring str("");
    ASSERT_EQUALS(str.count('a'), 0);
TEST_END()

TEST_BEGIN(c_str_constructor_count_gives_1)
    const Substring str("a");
    ASSERT_EQUALS(str.count('a'), 1);
TEST_END()

TEST_BEGIN(c_str_constructor_count_gives_2)
    const Substring str("aa");
    ASSERT_EQUALS(str.count('a'), 2);
TEST_END()

TEST_BEGIN(c_str_constructor_count_gives_3)
    const Substring str("aaa");
    ASSERT_EQUALS(str.count('a'), 3);
TEST_END()

TEST_BEGIN(c_str_constructor_count_gives_4)
    const Substring str("aaaa");
    ASSERT_EQUALS(str.count('a'), 4);
TEST_END()

TEST_BEGIN(c_str_constructor_count_gives_5)
    const Substring str("aaaaa");
    ASSERT_EQUALS(str.count('a'), 5);
TEST_END()

TEST_BEGIN(c_str_constructor_count_randomstr_gives_1)
    const Substring str("rqew0y81342itapwer8not2b3gon");
    ASSERT_EQUALS(str.count('a'), 1);
TEST_END()

TEST_BEGIN(c_str_constructor_count_randomstr_gives_2)
    const Substring str("rqew0y81342itapwer8nota2b3gon");
    ASSERT_EQUALS(str.count('a'), 2);
TEST_END()

TEST_BEGIN(c_str_constructor_count_randomstr_gives_3)
    const Substring str("rqeaw0y81342itapwer8nota2b3gon");
    ASSERT_EQUALS(str.count('a'), 3);
TEST_END()

TEST_BEGIN(c_str_constructor_count_randomstr_gives_4)
    const Substring str("rqewa0y81342itapwer8nota2b3agon");
    ASSERT_EQUALS(str.count('a'), 4);
TEST_END()

TEST_BEGIN(c_str_constructor_count_randomstr_gives_5)
    const Substring str("rqewa0y81342itapwer8notaa2b3agon");
    ASSERT_EQUALS(str.count('a'), 5);
TEST_END()

TEST_BEGIN(empty_c_str_constructor_equals_empty_c_string)
    const Substring str("");
    ASSERT_EQUALS(str, "");
TEST_END()

TEST_BEGIN(c_str_constructor_equals_c_string)
    const Substring str("Hello, world!");
    ASSERT_EQUALS(str, "Hello, world!");
TEST_END()

TEST_BEGIN(empty_c_str_constructor_equals_empty_string)
    const Substring str("");
    ASSERT_EQUALS(str, Substring(""));
TEST_END()

TEST_BEGIN(c_str_constructor_equals_string)
    const Substring str("Hello, world!");
    ASSERT_STR_EQ_STR(str, Substring("Hello, world!"));
TEST_END()

TEST_BEGIN(c_str_constructor_splits_to_strings_0)
    const Substring str("asdf,qwergui,zx");
    Substring substrings [16];
    str.split('#', substrings);
    ASSERT_EQUALS(substrings[0], "asdf,qwergui,zx");
    ASSERT_EQUALS(substrings[1], "");
    ASSERT_EQUALS(substrings[2], "");
    ASSERT_EQUALS(substrings[3], "");
    ASSERT_EQUALS(substrings[4], "");
    ASSERT_EQUALS(substrings[5], "");
    ASSERT_EQUALS(substrings[6], "");
    ASSERT_EQUALS(substrings[7], "");
TEST_END()

TEST_BEGIN(c_str_constructor_splits_to_strings_1)
    const Substring str("asdf,qwergui,zx");
    Substring substrings [16];
    str.split(',', substrings);
    ASSERT_EQUALS(substrings[0], "asdf");
    ASSERT_EQUALS(substrings[1], "qwergui");
    ASSERT_EQUALS(substrings[2], "zx");
    ASSERT_EQUALS(substrings[3], "");
    ASSERT_EQUALS(substrings[4], "");
    ASSERT_EQUALS(substrings[5], "");
    ASSERT_EQUALS(substrings[6], "");
    ASSERT_EQUALS(substrings[7], "");
TEST_END()

TEST_BEGIN(c_str_constructor_splits_to_strings_2)
    const Substring str(",asdf,qwergui,zx");
    Substring substrings [16];
    str.split(',', substrings);
    ASSERT_EQUALS(substrings[0], "");
    ASSERT_EQUALS(substrings[1], "asdf");
    ASSERT_EQUALS(substrings[2], "qwergui");
    ASSERT_EQUALS(substrings[3], "zx");
    ASSERT_EQUALS(substrings[4], "");
    ASSERT_EQUALS(substrings[5], "");
    ASSERT_EQUALS(substrings[6], "");
    ASSERT_EQUALS(substrings[7], "");
TEST_END()

TEST_BEGIN(c_str_constructor_splits_to_strings_3)
    const Substring str("asdf,qwergui,zx,");
    Substring substrings [16];
    str.split(',', substrings);
    ASSERT_EQUALS(substrings[0], "asdf");
    ASSERT_EQUALS(substrings[1], "qwergui");
    ASSERT_EQUALS(substrings[2], "zx");
    ASSERT_EQUALS(substrings[3], "");
    ASSERT_EQUALS(substrings[4], "");
    ASSERT_EQUALS(substrings[5], "");
    ASSERT_EQUALS(substrings[6], "");
    ASSERT_EQUALS(substrings[7], "");
TEST_END()

TEST_BEGIN(c_str_constructor_splits_to_strings_4)
    const Substring str(";digitalWrite(35, HIGH);analogRead(A3);;");
    Substring substrings [16];
    str.split(';', substrings);
    ASSERT_EQUALS(substrings[0], "");
    ASSERT_EQUALS(substrings[1], "digitalWrite(35, HIGH)");
    ASSERT_EQUALS(substrings[2], "analogRead(A3)");
    ASSERT_EQUALS(substrings[3], "");
    ASSERT_EQUALS(substrings[4], "");
    ASSERT_EQUALS(substrings[5], "");
    ASSERT_EQUALS(substrings[6], "");
    ASSERT_EQUALS(substrings[7], "");
TEST_END()

TEST_BEGIN(c_str_constructor_splits_to_strings_5)
    const Substring str("a,b,c,d,e");
    Substring substrings [16];
    str.split(',', substrings);
    ASSERT_EQUALS(substrings[0], "a");
    ASSERT_EQUALS(substrings[1], "b");
    ASSERT_EQUALS(substrings[2], "c");
    ASSERT_EQUALS(substrings[3], "d");
    ASSERT_EQUALS(substrings[4], "e");
    ASSERT_EQUALS(substrings[5], "");
    ASSERT_EQUALS(substrings[6], "");
    ASSERT_EQUALS(substrings[7], "");
TEST_END()

TEST_BEGIN(c_str_constructor_assigned_c_string)
    Substring str("Greetings from robot.");
    ASSERT_FALSE(str.isEmpty());
    ASSERT_EQUALS(str.getLength(), 21);
    ASSERT_EQUALS(str, "Greetings from robot.");
    const Substring &ref = (str = "Hello, world!");
    ASSERT_EQUALS(&ref, &str);
    ASSERT_FALSE(str.isEmpty());
    ASSERT_EQUALS(str.getLength(), 13);
    ASSERT_EQUALS(str, "Hello, world!");
TEST_END()

TEST_BEGIN(c_str_constructor_assigned_string)
    Substring str("Greetings from robot.");
    ASSERT_FALSE(str.isEmpty());
    ASSERT_EQUALS(str.getLength(), 21);
    ASSERT_EQUALS(str, "Greetings from robot.");
    const Substring another_string("Hello, world!");
    const Substring &ref = (str = another_string);
    ASSERT_EQUALS(&ref, &str);
    ASSERT_FALSE(str.isEmpty());
    ASSERT_EQUALS(str.getLength(), 13);
    ASSERT_EQUALS(str, "Hello, world!");
TEST_END()

}

namespace lexicographical_comparison {

TEST_BEGIN(empty_str_vs_empty_str)
    Substring str1("");
    Substring str2("");
    ASSERT_STR_EQ_STR(str1, str2);
TEST_END()

TEST_BEGIN(empty_str_vs_single_char_str)
    Substring str1("");
    Substring str2("a");
    ASSERT_STR_LT_STR(str1, str2);
TEST_END()

TEST_BEGIN(single_char_str_vs_other_single_char_str)
    Substring str1("a");
    Substring str2("b");
    ASSERT_STR_LT_STR(str1, str2);
TEST_END()

TEST_BEGIN(lower_single_char_str_vs_upper_single_char_str)
    Substring str1("A");
    Substring str2("a");
    ASSERT_STR_LT_STR(str1, str2);
TEST_END()

TEST_BEGIN(str_vs_substr)
    Substring str1("abc");
    Substring str2("abcd");
    ASSERT_STR_LT_STR(str1, str2);
TEST_END()

TEST_BEGIN(parent_member_str_vs_child_member_str)
    Substring str1("top.yhchoi.jm9.xrcu");
    Substring str2("top.yhchoi.jm9.xrcu.hardware");
    ASSERT_STR_LT_STR(str1, str2);
TEST_END()

TEST_BEGIN(str_vs_same_str)
    Substring str1("top.yhchoi.jm9.xrcu.hardware");
    Substring str2("top.yhchoi.jm9.xrcu.hardware");
    ASSERT_STR_EQ_STR(str1, str2);
TEST_END()

}

using namespace empty_constructor;
using namespace c_string_constructor;
using namespace lexicographical_comparison;

const testfunc_t functions [] = {
    test_empty_testcase,
    test_empty_constructor_memory_leak,
    test_empty_constructor_gives_empty_string,
    test_empty_constructor_gives_zero_length,
    test_empty_constructor_gives_null_char,
    test_empty_constructor_copy_to_buffer_gives_empty_string,
    test_empty_constructor_substring_1_param_gives_empty_string,
    test_empty_constructor_substring_with_0_length_gives_empty_string,
    test_empty_constructor_substring_2_param_gives_empty_string,
    test_empty_constructor_remove_head_spaces_gives_empty_string,
    test_empty_constructor_remove_tail_spaces_gives_empty_string,
    test_empty_constructor_trim_gives_empty_string,
    test_empty_constructor_index_of_somechar_gives_length,
    test_empty_constructor_last_index_of_somechar_gives_length,
    test_empty_constructor_count_somechar_gives_0,
    test_empty_constructor_equals_empty_c_string,
    test_empty_constructor_equals_empty_string,
    test_empty_constructor_splits_to_empty_string,
    test_empty_constructor_assigned_c_string,
    test_empty_constructor_assigned_string,
    test_c_string_constructor_memory_leak,
    test_empty_c_string_constructor_gives_empty_string,
    test_c_string_1_constructor_gives_non_empty_string,
    test_c_string_2_constructor_gives_non_empty_string,
    test_c_string_3_constructor_gives_non_empty_string,
    test_c_string_4_constructor_gives_non_empty_string,
    test_c_string_5_constructor_gives_non_empty_string,
    test_empty_c_str_constructor_gives_zero_length,
    test_c_str_1_constructor_gives_1_length,
    test_c_str_2_constructor_gives_2_length,
    test_c_str_3_constructor_gives_3_length,
    test_c_str_4_constructor_gives_4_length,
    test_c_str_5_constructor_gives_5_length,
    test_empty_c_str_constructor_gives_null_char,
    test_c_str_1_constructor_gives_corresponding_chars,
    test_c_str_2_constructor_gives_corresponding_chars,
    test_c_str_3_constructor_gives_corresponding_chars,
    test_c_str_4_constructor_gives_corresponding_chars,
    test_c_str_5_constructor_gives_corresponding_chars,
    test_empty_c_str_constructor_copy_to_buffer_gives_empty_string,
    test_c_str_1_constructor_copy_to_buffer_gives_corresponding_string,
    test_c_str_2_constructor_copy_to_buffer_gives_corresponding_string,
    test_c_str_3_constructor_copy_to_buffer_gives_corresponding_string,
    test_c_str_4_constructor_copy_to_buffer_gives_corresponding_string,
    test_c_str_5_constructor_copy_to_buffer_gives_corresponding_string,
    test_c_str_5_constructor_substring_remove_head_1_char,
    test_c_str_5_constructor_substring_remove_head_2_chars,
    test_c_str_5_constructor_substring_remove_head_3_chars,
    test_c_str_5_constructor_substring_remove_head_4_chars,
    test_c_str_5_constructor_substring_remove_head_5_chars,
    test_c_str_5_constructor_substring_remove_head_6_chars,
    test_c_str_5_constructor_substring_remove_head_7_chars,
    test_c_str_5_constructor_substring_with_0_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_with_1_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_with_2_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_with_3_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_with_4_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_with_5_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_with_6_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_with_7_offset_0_length_gives_empty_string,
    test_c_str_5_constructor_substring_0_1,
    test_c_str_5_constructor_substring_0_2,
    test_c_str_5_constructor_substring_0_3,
    test_c_str_5_constructor_substring_0_4,
    test_c_str_5_constructor_substring_0_5,
    test_c_str_5_constructor_substring_0_6,
    test_c_str_5_constructor_substring_0_7,
    test_c_str_5_constructor_substring_1_1,
    test_c_str_5_constructor_substring_1_2,
    test_c_str_5_constructor_substring_1_3,
    test_c_str_5_constructor_substring_1_4,
    test_c_str_5_constructor_substring_1_5,
    test_c_str_5_constructor_substring_1_6,
    test_c_str_5_constructor_substring_1_7,
    test_c_str_5_constructor_substring_2_1,
    test_c_str_5_constructor_substring_2_2,
    test_c_str_5_constructor_substring_2_3,
    test_c_str_5_constructor_substring_2_4,
    test_c_str_5_constructor_substring_2_5,
    test_c_str_5_constructor_substring_2_6,
    test_c_str_5_constructor_substring_2_7,
    test_c_str_5_constructor_substring_3_1,
    test_c_str_5_constructor_substring_3_2,
    test_c_str_5_constructor_substring_3_3,
    test_c_str_5_constructor_substring_3_4,
    test_c_str_5_constructor_substring_3_5,
    test_c_str_5_constructor_substring_3_6,
    test_c_str_5_constructor_substring_3_7,
    test_c_str_5_constructor_substring_4_1,
    test_c_str_5_constructor_substring_4_2,
    test_c_str_5_constructor_substring_4_3,
    test_c_str_5_constructor_substring_4_4,
    test_c_str_5_constructor_substring_4_5,
    test_c_str_5_constructor_substring_4_6,
    test_c_str_5_constructor_substring_4_7,
    test_c_str_5_constructor_substring_5_1,
    test_c_str_5_constructor_substring_5_2,
    test_c_str_5_constructor_substring_5_3,
    test_c_str_5_constructor_substring_5_4,
    test_c_str_5_constructor_substring_5_5,
    test_c_str_5_constructor_substring_5_6,
    test_c_str_5_constructor_substring_5_7,
    test_c_str_5_constructor_substring_6_1,
    test_c_str_5_constructor_substring_6_2,
    test_c_str_5_constructor_substring_6_3,
    test_c_str_5_constructor_substring_6_4,
    test_c_str_5_constructor_substring_6_5,
    test_c_str_5_constructor_substring_6_6,
    test_c_str_5_constructor_substring_6_7,
    test_c_str_5_constructor_substring_7_1,
    test_c_str_5_constructor_substring_7_2,
    test_c_str_5_constructor_substring_7_3,
    test_c_str_5_constructor_substring_7_4,
    test_c_str_5_constructor_substring_7_5,
    test_c_str_5_constructor_substring_7_6,
    test_c_str_5_constructor_substring_7_7,
    test_c_str_5_constructor_substring_1_substring_0_3,
    test_c_str_5_constructor_substring_0_4_substring_1,
    test_c_str_5_constructor_substring_2_substring_0_2,
    test_c_str_5_constructor_substring_1_substring_1_2,
    test_c_str_5_constructor_substring_0_4_substring_2,
    test_c_str_5_constructor_substring_1_3_substring_1,
    test_c_str_5_constructor_substring_6_12_substring_3_5_substring_4_8,
    test_c_str_constructor_remove_head_spaces_gives_corresponding_string_1,
    test_c_str_constructor_remove_head_spaces_gives_corresponding_string_2,
    test_c_str_constructor_remove_head_spaces_gives_corresponding_string_3,
    test_c_str_constructor_remove_head_spaces_gives_corresponding_string_4,
    test_c_str_constructor_remove_head_spaces_gives_corresponding_string_5,
    test_c_str_constructor_remove_head_spaces_gives_corresponding_string_6,
    test_c_str_constructor_remove_tail_spaces_gives_corresponding_string_1,
    test_c_str_constructor_remove_tail_spaces_gives_corresponding_string_2,
    test_c_str_constructor_remove_tail_spaces_gives_corresponding_string_3,
    test_c_str_constructor_remove_tail_spaces_gives_corresponding_string_4,
    test_c_str_constructor_remove_tail_spaces_gives_corresponding_string_5,
    test_c_str_constructor_remove_tail_spaces_gives_corresponding_string_6,
    test_c_str_constructor_trim_gives_corresponding_string_1,
    test_c_str_constructor_trim_gives_corresponding_string_2,
    test_c_str_constructor_trim_gives_corresponding_string_3,
    test_c_str_constructor_trim_gives_corresponding_string_4,
    test_c_str_constructor_trim_gives_corresponding_string_5,
    test_c_str_constructor_trim_gives_corresponding_string_6,
    test_c_str_constructor_trim_gives_corresponding_string_7,
    test_c_str_constructor_trim_gives_corresponding_string_8,
    test_c_str_constructor_trim_gives_corresponding_string_9,
    test_c_str_constructor_trim_gives_corresponding_string_10,
    test_c_str_constructor_trim_gives_corresponding_string_11,
    test_c_str_constructor_trim_gives_corresponding_string_12,
    test_c_str_constructor_trim_gives_corresponding_string_13,
    test_c_str_constructor_trim_gives_corresponding_string_14,
    test_c_str_constructor_trim_gives_corresponding_string_15,
    test_c_str_constructor_trim_gives_corresponding_string_16,
    test_c_str_constructor_index_of_first_char_gives_0,
    test_c_str_constructor_index_of_first_char_recurring_gives_0,
    test_c_str_constructor_index_of_second_char_recurring_gives_1,
    test_c_str_constructor_index_of_middle_char_gives_index,
    test_c_str_constructor_index_of_second_last_char_gives_second_last_index,
    test_c_str_constructor_index_of_last_char_gives_last_index,
    test_c_str_constructor_index_of_nonexisting_char_gives_length,
    test_c_str_constructor_last_index_of_first_char_gives_0,
    test_c_str_constructor_last_index_of_first_char_recurring_gives_middle_index,
    test_c_str_constructor_last_index_of_second_char_recurring_gives_middle_index,
    test_c_str_constructor_last_index_of_middle_char_gives_index,
    test_c_str_constructor_last_index_of_second_last_char_gives_second_last_index,
    test_c_str_constructor_last_index_of_last_char_gives_last_index,
    test_c_str_constructor_last_index_of_nonexisting_char_gives_length,
    test_empty_c_str_constructor_count_somechar_gives_0,
    test_c_str_constructor_count_gives_1,
    test_c_str_constructor_count_gives_2,
    test_c_str_constructor_count_gives_3,
    test_c_str_constructor_count_gives_4,
    test_c_str_constructor_count_gives_5,
    test_c_str_constructor_count_randomstr_gives_1,
    test_c_str_constructor_count_randomstr_gives_2,
    test_c_str_constructor_count_randomstr_gives_3,
    test_c_str_constructor_count_randomstr_gives_4,
    test_c_str_constructor_count_randomstr_gives_5,
    test_empty_c_str_constructor_equals_empty_c_string,
    test_c_str_constructor_equals_c_string,
    test_empty_c_str_constructor_equals_empty_string,
    test_c_str_constructor_equals_string,
    test_c_str_constructor_splits_to_strings_0,
    test_c_str_constructor_splits_to_strings_1,
    test_c_str_constructor_splits_to_strings_2,
    test_c_str_constructor_splits_to_strings_3,
    test_c_str_constructor_splits_to_strings_4,
    test_c_str_constructor_splits_to_strings_5,
    test_c_str_constructor_assigned_c_string,
    test_c_str_constructor_assigned_string,
    test_empty_str_vs_empty_str,
    test_empty_str_vs_single_char_str,
    test_single_char_str_vs_other_single_char_str,
    test_lower_single_char_str_vs_upper_single_char_str,
    test_str_vs_substr,
    test_parent_member_str_vs_child_member_str,
    test_str_vs_same_str,
};

MAIN();
