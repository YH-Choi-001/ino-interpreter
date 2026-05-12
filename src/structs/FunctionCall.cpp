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
