/**
 * Unit tests for the function registry class.
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

#include "../../../src/structs/FunctionRegistry.h"

using ino_interpreter::structs::FunctionRegistry;
using ino_interpreter::structs::FunctionDeclaration;
using ino_interpreter::structs::FunctionImplementation;
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

std::ostream &operator<<(std::ostream &os, const FunctionImplementation &fi) {
    os << "fi of " << fi.getArgCount() << " arguments";
    return os;
}

namespace {

#define ASSERT_REG_HAS_DECL_IMPL(reg,decl,impl) { \
    ASSERT_IS_NOT_NULLPTR(reg.getFunction(decl)); \
    ASSERT_EQUALS(*(reg.getFunction(decl)), impl); \
    ASSERT_EQUALS(reg.getFunction(decl)->getArgCount(), impl.getArgCount()); \
    \
    ASSERT_IS_NOT_NULLPTR(reg.resolve(decl)); \
    ASSERT_EQUALS(*(reg.resolve(decl)), impl); \
    ASSERT_EQUALS(reg.resolve(decl)->getArgCount(), impl.getArgCount()); \
}

#define ASSERT_INSERT_NEW_FUNCTION(reg,declaration,implementation) { \
    FunctionDeclaration &decl = declaration; \
    FunctionImplementation &impl = implementation; \
    ASSERT_EQUALS(decl.getArgCount(), impl.getArgCount()); \
    ASSERT_IS_NULLPTR(reg.getFunction(decl)); \
    const size_t beforeFuncCount = reg.getFunctionCount(); \
    reg.insertFunction(decl, impl); \
    const size_t afterFuncCount = reg.getFunctionCount(); \
    ASSERT_EQUALS(beforeFuncCount + 1, afterFuncCount); \
    ASSERT_REG_HAS_DECL_IMPL(reg,decl,impl); \
}

#define ASSERT_RUNNING_CMD_RETURNS(cmdstr, expectedResult) { \
    FunctionCall call(cmdstr); \
    FunctionImplementation *const impl = reg.resolve(call); \
    ASSERT_IS_NOT_NULLPTR(impl); \
    ASSERT_EQUALS(call.getArgCount(), impl->getArgCount()); \
    const FunctionImplementation::return_t actualResult = impl->execute(call); \
    ASSERT_EQUALS(actualResult, (expectedResult)); \
}

#define ASSERT_CMD_NOT_RESOLVED(cmdstr) { \
    FunctionCall call(cmdstr); \
    FunctionImplementation *const impl = reg.resolve(call); \
    ASSERT_IS_NULLPTR(impl); \
}


#define DEFINE_SIMPLE_FIXTURES() \
    FunctionRegistry reg; \
    { \
        ASSERT_EQUALS(reg.getFunctionCount(), 0); \
        ASSERT_EQUALS(reg.getSubRegistryCount(), 0); \
        FunctionDeclaration declPinMode("pinMode", 2); \
        FunctionDeclaration declDigitalWrite("digitalWrite", 2); \
        FunctionDeclaration declDigitalRead("digitalRead", 1); \
        FunctionDeclaration declAnalogWrite("analogWrite", 2); \
        FunctionDeclaration declAnalogRead("analogRead", 1); \
        FunctionImplementation implPinMode([](Argument pin, Argument mode) -> FunctionImplementation::return_t { \
            return 23 * pin + 29 * mode + 1; \
        }); \
        FunctionImplementation implDigitalWrite([](Argument pin, Argument state) -> FunctionImplementation::return_t { \
            return 23 * pin + 29 * state + 2; \
        }); \
        FunctionImplementation implDigitalRead([](Argument pin) -> FunctionImplementation::return_t { \
            return 23 * pin + 3; \
        }); \
        FunctionImplementation implAnalogWrite([](Argument pin, Argument state) -> FunctionImplementation::return_t { \
            return 23 * pin + 29 * state + 4; \
        }); \
        FunctionImplementation implAnalogRead([](Argument pin) -> FunctionImplementation::return_t { \
            return 23 * pin + 5; \
        }); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declPinMode, implPinMode); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declDigitalWrite, implDigitalWrite); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declDigitalRead, implDigitalRead); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declAnalogWrite, implAnalogWrite); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declAnalogRead, implAnalogRead); \
        ASSERT_EQUALS(reg.getFunctionCount(), 5); \
        ASSERT_EQUALS(reg.getSubRegistryCount(), 0); \
    }


#define ASSERT_SIMPLE_FIXTURES_OK(prefix) { \
    ASSERT_RUNNING_CMD_RETURNS(prefix "pinMode(9, 4)", 23 * 9 + 29 * 4 + 1); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "digitalWrite(9, 4)", 23 * 9 + 29 * 4 + 2); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "digitalRead(9)", 23 * 9 + 3); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "analogWrite(9, 4)", 23 * 9 + 29 * 4 + 4); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "analogRead(9)", 23 * 9 + 5); \
}

#define ASSERT_UNDEFINED_SIMPLE_FIXTURES_NOT_RESOLVED(prefix) { \
    ASSERT_CMD_NOT_RESOLVED(prefix "pinMode(9)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "digitalWrite(9)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "digitalRead(9, 4)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "analogWrite(9)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "analogRead(9, 4)"); \
}

#define ASSERT_SIMPLE_FIXTURES_OK_ONLY(prefix) { \
    ASSERT_SIMPLE_FIXTURES_OK(prefix); \
    ASSERT_UNDEFINED_SIMPLE_FIXTURES_NOT_RESOLVED(prefix); \
}


#define DEFINE_OVERLOADING_FIXTURES() \
    { \
        FunctionDeclaration declPinMode("pinMode", 1); \
        FunctionDeclaration declDigitalWrite("digitalWrite", 1); \
        FunctionDeclaration declDigitalRead("digitalRead", 2); \
        FunctionDeclaration declAnalogWrite("analogWrite", 1); \
        FunctionDeclaration declAnalogRead("analogRead", 2); \
        FunctionImplementation implPinMode([](Argument pin) -> FunctionImplementation::return_t { \
            return 23 * pin + 6; \
        }); \
        FunctionImplementation implDigitalWrite([](Argument pin) -> FunctionImplementation::return_t { \
            return 23 * pin + 7; \
        }); \
        FunctionImplementation implDigitalRead([](Argument pin, Argument state) -> FunctionImplementation::return_t { \
            return 23 * pin + 29 * state + 8; \
        }); \
        FunctionImplementation implAnalogWrite([](Argument pin) -> FunctionImplementation::return_t { \
            return 23 * pin + 9; \
        }); \
        FunctionImplementation implAnalogRead([](Argument pin, Argument state) -> FunctionImplementation::return_t { \
            return 23 * pin + 29 * state + 10; \
        }); \
        const size_t prevFuncCount = reg.getFunctionCount(); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declPinMode, implPinMode); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declDigitalWrite, implDigitalWrite); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declDigitalRead, implDigitalRead); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declAnalogWrite, implAnalogWrite); \
        ASSERT_INSERT_NEW_FUNCTION(reg, declAnalogRead, implAnalogRead); \
        ASSERT_EQUALS(reg.getFunctionCount(), prevFuncCount + 5); \
        ASSERT_EQUALS(reg.getSubRegistryCount(), 0); \
    }


#define ASSERT_OVERLOADING_FIXTURES_OK(prefix) { \
    ASSERT_RUNNING_CMD_RETURNS(prefix "pinMode(9)", 23 * 9 + 6); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "digitalWrite(9)", 23 * 9 + 7); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "digitalRead(9, 4)", 23 * 9 + 29 * 4 + 8); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "analogWrite(9)", 23 * 9 + 9); \
    ASSERT_RUNNING_CMD_RETURNS(prefix "analogRead(9, 4)", 23 * 9 + 29 * 4 + 10); \
}

#define ASSERT_UNDEFINED_OVERLOADING_FIXTURES_NOT_RESOLVED(prefix) { \
    ASSERT_CMD_NOT_RESOLVED(prefix "pinMode(9, 4, 5)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "digitalWrite(9, 4, 5)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "digitalRead(9, 4, 5)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "analogWrite(9, 4, 5)"); \
    ASSERT_CMD_NOT_RESOLVED(prefix "analogRead(9, 4, 5)"); \
}

#define ASSERT_OVERLOADING_FIXTURES_OK_ONLY(prefix) { \
    ASSERT_OVERLOADING_FIXTURES_OK(prefix); \
    ASSERT_UNDEFINED_OVERLOADING_FIXTURES_NOT_RESOLVED(prefix); \
}

#define ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY(prefix) { \
    ASSERT_SIMPLE_FIXTURES_OK(prefix); \
    ASSERT_OVERLOADING_FIXTURES_OK_ONLY(prefix); \
}

#define ASSERT_INSERT_SUB_REGISTRY_OK(reg,name,subreg) { \
    const size_t prevSubRegCount = reg.getSubRegistryCount(); \
    reg.insertSubRegistry((name), (subreg)); \
    ASSERT_EQUALS(reg.getSubRegistryCount(), prevSubRegCount + 1); \
    ASSERT_IS_NOT_NULLPTR(reg.getSubRegistry((name))); \
}


TEST_BEGIN(empty_testcase)
    result.passed = true;
TEST_END()

TEST_BEGIN(default_constructor_memory_leak)
    const FunctionRegistry reg;
TEST_END()

TEST_BEGIN(copy_constructor_memory_leak)
    const FunctionRegistry reg0;
    const FunctionRegistry reg1(reg0);
TEST_END()

TEST_BEGIN(insert_functions_memory_leak)
    DEFINE_SIMPLE_FIXTURES();
TEST_END()

TEST_BEGIN(simple_functions_resolvable)
    DEFINE_SIMPLE_FIXTURES();
    ASSERT_SIMPLE_FIXTURES_OK_ONLY();
TEST_END()

TEST_BEGIN(insert_overloading_functions_memory_leak)
    DEFINE_SIMPLE_FIXTURES();
    DEFINE_OVERLOADING_FIXTURES();
TEST_END()

TEST_BEGIN(overloading_functions_resolvable)
    DEFINE_SIMPLE_FIXTURES();
    ASSERT_SIMPLE_FIXTURES_OK_ONLY();
    DEFINE_OVERLOADING_FIXTURES();
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY();
TEST_END()

TEST_BEGIN(insert_sub_registry_memory_leak)
    DEFINE_SIMPLE_FIXTURES();
    DEFINE_OVERLOADING_FIXTURES();
    ASSERT_INSERT_SUB_REGISTRY_OK(reg, "jm9", reg);
TEST_END()

TEST_BEGIN(sub_registry_resolvable)
    DEFINE_SIMPLE_FIXTURES();
    ASSERT_SIMPLE_FIXTURES_OK_ONLY();
    DEFINE_OVERLOADING_FIXTURES();
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY();
    ASSERT_INSERT_SUB_REGISTRY_OK(reg, "jm9", reg);
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY();
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY("jm9.");
TEST_END()

TEST_BEGIN(multi_layer_sub_registries_resolvable)
    DEFINE_SIMPLE_FIXTURES();
    ASSERT_SIMPLE_FIXTURES_OK_ONLY();
    DEFINE_OVERLOADING_FIXTURES();
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY();
    ASSERT_INSERT_SUB_REGISTRY_OK(reg, "jm9", reg);
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY();
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY("jm9.");
    ASSERT_INSERT_SUB_REGISTRY_OK((*reg.getSubRegistry("jm9")), "xrcu", reg);
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY();
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY("jm9.");
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY("jm9.xrcu.");
    ASSERT_SIMPLE_AND_OVERLOADING_FIXTURES_OK_ONLY("jm9.xrcu.jm9.");
TEST_END()

}

const testfunc_t functions [] = {
    test_empty_testcase,
    test_default_constructor_memory_leak,
    test_copy_constructor_memory_leak,
    test_insert_functions_memory_leak,
    test_simple_functions_resolvable,
    test_insert_overloading_functions_memory_leak,
    test_overloading_functions_resolvable,
    test_insert_sub_registry_memory_leak,
    test_sub_registry_resolvable,
    test_multi_layer_sub_registries_resolvable,
};

MAIN();
