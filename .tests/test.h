/**
 * @file test.h Macros and definitions of the testing framework.
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

#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

#include "mem_leak.h"

namespace testing_framework {

struct testcase_result_t {
    bool passed;
    size_t line;
    std::string reason;

    static const bool DEFAULT_PASSED_STATE = true;
    static const size_t DEFAULT_LINE = 0;
    static const char *const DEFAULT_REASON;

    testcase_result_t() :
        passed(DEFAULT_PASSED_STATE),
        line(DEFAULT_LINE),
        reason(DEFAULT_REASON) {}
};
const char *const testcase_result_t::DEFAULT_REASON = "no reason provided";

typedef void (*testfunc_t)(testcase_result_t &, std::stringstream &);

namespace {
static size_t testcase_number = 1;
static size_t failed_testcase_count = 0;
static bool colored_output = true;
namespace terminal {
    class Color {
        private:
            const char *const string_rep;
        public:
            Color(const char *const string_rep) : string_rep(string_rep) {}
            inline const char *get_string_rep() const { return string_rep; }
    };
    namespace colors {
        const Color RED = "\33[31m";
        const Color YELLOW = "\33[33m";
        const Color GREEN = "\33[32m";
        const Color BLUE = "\33[34m";
        const Color RESET = "\33[0m";
    }
}
}

std::ostream &operator<<(std::ostream &os, const terminal::Color &color) {
    if (colored_output) {
        os << color.get_string_rep();
    }
    return os;
}

void test(testfunc_t func) {
    testcase_result_t result;
    result.reason.reserve(2048); // avoid malloc resizing when a long reason is provided
    std::stringstream reasonstream;
    tests::mem_leak::reset_malloc_count();
    func(result, reasonstream);
    const size_t malloc_count = tests::mem_leak::get_malloc_count();
    const bool is_memory_leaked = tests::mem_leak::has_memory_leaked();
    {
        // reasonstream handling
        const std::string reasonstr = reasonstream.str();
        if (
            !result.passed &&
            (result.reason == testing_framework::testcase_result_t::DEFAULT_REASON) &&
            !reasonstr.empty()
        ) {
            result.reason = reasonstr;
        }
    }
    std::stringstream sstream;
    sstream << "Testcase #" << testcase_number << " at line " << result.line << ": ";
    if (is_memory_leaked) {
        std::stringstream reasonstream;
        reasonstream << "Memory leak! You forgot " << malloc_count << " delete(s).";
        const std::string reasonstring = reasonstream.str();
        if (result.passed) {
            result.passed = false;
            result.reason = reasonstring;
        } else {
            result.reason += "; " + reasonstring;
        }
    }
    if (result.passed) {
        sstream << "passed.";
        std::cout << terminal::colors::GREEN;
    } else {
        sstream << "failed: " << result.reason;
        failed_testcase_count++;
        std::cout << terminal::colors::RED;
    }
    std::cout << sstream.str();
    std::cout << terminal::colors::RESET << std::endl;
    testcase_number++;
}

size_t get_failed_testcase_count() {
    return failed_testcase_count;
}

}

using testing_framework::testfunc_t;
using testing_framework::operator<<;

// should be defined in test*.cpp
extern const testing_framework::testfunc_t functions [];

#define TEST_BEGIN(testcase_name) \
void test_##testcase_name(testing_framework::testcase_result_t &result, std::stringstream &reasonstream) { \
    { \
        result.line = __LINE__; \
    }

#define TEST_END() \
}


#define ASSERT_EQUALS(x,y) { \
    if (!((x) == (y))) { \
        result.passed = false; \
        reasonstream << #x << " = " << (x) << " should be, but doesn\'t equal to " << #y << " = " << (y) << "."; \
    } \
}

#define _ASSERT_FLOATING_POINT_EQUALS(x,y,tolerance,type_t) { \
    const type_t eval_x = (x); \
    const type_t eval_y = (y); \
    type_t delta = (eval_x - eval_y); \
    if (delta < 0) { \
        delta = -delta; \
    } \
    const type_t abstolerance = (tolerance > 0) ? tolerance : -tolerance; \
    if (delta > abstolerance) { \
        result.passed = false; \
        reasonstream << #x << " = " << eval_x << " should be, but doesn\'t equal to " << #y << " = " << eval_y << "."; \
    } \
}

#define ASSERT_FLOAT_EQUALS(x,y,tolerance) \
    _ASSERT_FLOATING_POINT_EQUALS(x,y,tolerance,float)

#define ASSERT_DOUBLE_EQUALS(x,y,tolerance) \
    _ASSERT_FLOATING_POINT_EQUALS(x,y,tolerance,double)

#define ASSERT_CSTR_EQUALS(x,y) { \
    if (std::strcmp((x), (y)) != 0) { \
        result.passed = false; \
        reasonstream << #x << " = " << (x) << " should be, but doesn\'t equal to " << #y << " = " << (y) << "."; \
    } \
}

#define ASSERT_NOT_EQUALS(x,y) { \
    if (!((x) != (y))) { \
        result.passed = false; \
        reasonstream << #x << " = " << (x) << " should not, but equals to " << #y << " = " << (y) << "."; \
    } \
}

#define ASSERT_TRUE(x) { \
    if (!(x)) { \
        result.passed = false; \
        reasonstream << #x << " should be true, but is false."; \
    } \
}

#define ASSERT_FALSE(x) { \
    if (x) { \
        result.passed = false; \
        reasonstream << #x << " should be false, but is true."; \
    } \
}

#define ASSERT_IS_NULLPTR(x) { \
    const void *const ptr = (x); \
    if ((ptr) != nullptr) { \
        result.passed = false; \
        reasonstream << #x << " should be nullptr, but is " << ptr << "."; \
    } \
}

#define ASSERT_IS_NOT_NULLPTR(x) { \
    if ((x) == nullptr) { \
        result.passed = false; \
        reasonstream << #x << " should not be nullptr, but is nullptr."; \
    } \
}


#define ALL_TESTS_BEGIN() { \
    std::cout << testing_framework::terminal::colors::YELLOW << "Testing " \
    << __BASE_FILE__ << testing_framework::terminal::colors::RESET << std::endl; \
}

#define TEST_ALL() { \
    for (const testfunc_t func : functions) { \
        test(func); \
    } \
}

#define ALL_TESTS_END() { \
    const size_t failed_testcase_count = \
        testing_framework::get_failed_testcase_count(); \
    std::stringstream line_contents; \
    if (failed_testcase_count == 0) { \
        line_contents << testing_framework::terminal::colors::GREEN << "All passed: "; \
    } else { \
        line_contents << testing_framework::terminal::colors::RED << failed_testcase_count << " failed: "; \
    } \
    line_contents << __BASE_FILE__ << testing_framework::terminal::colors::RESET; \
    std::cout << line_contents.str() << std::endl; \
    return failed_testcase_count; \
}

#define MAIN() int main(const int argc, const char **argv) { \
    for (int i = 1; i < argc; i++) { \
        if (std::strcmp(argv[i], "--no-color") == 0) { \
            testing_framework::colored_output = false; \
        } \
    } \
    ALL_TESTS_BEGIN() \
    TEST_ALL() \
    ALL_TESTS_END() \
}

#endif // #ifndef TEST_H