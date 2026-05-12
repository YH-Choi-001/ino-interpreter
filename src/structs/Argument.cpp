#include "Argument.h"

#include <stdlib.h>

using ino_interpreter::structs::Argument;
using ino_interpreter::structs::util::Substring;

// size_t Argument::findIndexOfNonFloat(const Substring str) {
//     size_t index = 0;
//     if (str[0] == '-' || str[0] == '+') {
//         index++;
//     }
//     const size_t stringRepLength = str.getLength();
//     bool dotEncountered = false;
//     for (; index < stringRepLength; index++) {
//         const char c = str[index];
//         if (c == '.') {
//             if (dotEncountered) {
//                 break;
//             }
//             dotEncountered = true;
//         } else if (c < '0' || c > '9') {
//             break;
//         }
//     }
//     return index;
// }

void Argument::setValue(const Substring str) {
    char cbuf [str.getLength() + 1];
    str.copyTo(cbuf);
    value = atof(cbuf);
}

Argument::Argument() :
    stringRep()
{
    setValue(stringRep);
}

Argument::Argument(Substring str) :
    stringRep(str.trim())
{
    setValue(stringRep);
}

Argument::Argument(const Argument &ref) :
    stringRep(ref.stringRep),
    value(ref.value)
{
    //
}

Argument::operator float() const {
    return value;
}

Argument::operator Substring() const {
    return stringRep;
}
