/**
 * Implementation of function call class.
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

#include "FunctionCall.h"

using ino_interpreter::structs::Argument;
using ino_interpreter::structs::FunctionCall;
using ino_interpreter::structs::util::Substring;

FunctionCall::factory_t FunctionCall::factory(Substring stringRep) {
    factory_t factory;
    stringRep = stringRep.trim();
    const size_t openParenthesisIndex = stringRep.indexOf('(');

    factory.identifier = stringRep.substring(0, openParenthesisIndex).trim();
    const Substring remainder = stringRep.substring(openParenthesisIndex + 1).trim();
    const size_t closeParenthesisIndex = remainder.indexOf(')');
    const Substring argList = remainder.substring(0, closeParenthesisIndex).trim();
    const char ARG_SEPARATOR = ',';

    factory.argCount = argList.isEmpty() ? 0 : argList.count(ARG_SEPARATOR) + 1;

    Substring argStrings [factory.argCount];
    argList.split(ARG_SEPARATOR, argStrings);

    factory.args = new const Argument* [factory.argCount];
    for (size_t i = 0; i < factory.argCount; i++) {
        factory.args[i] = new Argument(argStrings[i].trim());
    }
    return factory;
}

FunctionCall::FunctionCall() :
    FunctionDeclaration(Substring(), 0),
    args(nullptr)
{
    //
}

FunctionCall::FunctionCall(const FunctionCall &ref) :
    FunctionDeclaration(Substring(), 0),
    args(nullptr)
{
    //
}

FunctionCall::FunctionCall(factory_t f) :
    FunctionDeclaration(f.identifier, f.argCount),
    args(f.args)
{
    //
}

FunctionCall::FunctionCall(Substring stringRep) :
    FunctionCall(factory(stringRep))
{
    //
}

FunctionCall::~FunctionCall() {
    if (args != nullptr) {
        const size_t argCount = getArgCount();
        for (size_t i = 0; i < argCount; i++) {
            delete args[i];
        }
        delete[] args;
        args = nullptr;
    }
}

const Argument *FunctionCall::getArg(const size_t index) const {
    if (index >= getArgCount()) {
        return nullptr;
    }
    return args[index];
}
