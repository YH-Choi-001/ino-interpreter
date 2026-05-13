/**
 * Implementation of argument class.
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
