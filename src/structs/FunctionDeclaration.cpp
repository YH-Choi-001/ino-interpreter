#include "FunctionDeclaration.h"

using ino_interpreter::structs::FunctionDeclaration;
using ino_interpreter::structs::util::Substring;

FunctionDeclaration::FunctionDeclaration(
    const Substring identifier,
    const size_t argCount
) :
    identifier(identifier),
    argCount(argCount)
{
    //
}

FunctionDeclaration::FunctionDeclaration(
    const FunctionDeclaration &ref
) :
    identifier(ref.identifier),
    argCount(ref.argCount)
{
    //
}

Substring FunctionDeclaration::getIdentifier() const {
    return identifier;
}

size_t FunctionDeclaration::getArgCount() const {
    return argCount;
}

bool FunctionDeclaration::operator==(const FunctionDeclaration &rhs) const {
    if (argCount != rhs.argCount) {
        return false;
    }
    return identifier == rhs.identifier;
}

int FunctionDeclaration::compare(const FunctionDeclaration &lhs, const FunctionDeclaration &rhs) {
    const int idDiff = Substring::compare(lhs.identifier, rhs.identifier);
    if (idDiff != 0) {
        return idDiff;
    }
    return (signed int)lhs.argCount - (signed int)rhs.argCount;
}

bool FunctionDeclaration::operator<(const FunctionDeclaration &rhs) const {
    return compare((*this), rhs) < 0;
}

bool FunctionDeclaration::operator<=(const FunctionDeclaration &rhs) const {
    return compare((*this), rhs) <= 0;
}

bool FunctionDeclaration::operator>(const FunctionDeclaration &rhs) const {
    return compare((*this), rhs) > 0;
}

bool FunctionDeclaration::operator>=(const FunctionDeclaration &rhs) const {
    return compare((*this), rhs) >= 0;
}
