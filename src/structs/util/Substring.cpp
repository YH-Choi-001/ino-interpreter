/**
 * Implementation of substring class.
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

#include "Substring.h"

using ino_interpreter::structs::util::Substring;

size_t Substring::strlen(const char *str) {
    if (str == nullptr) {
        return 0;
    }
    size_t len = 0;
    while ((*str) != '\0') {
        len++;
        str++;
    }
    return len;
}

Substring::Substring() :
    cstr(nullptr),
    length(0)
{
    //
}

Substring::Substring(const char *const initStr, const size_t initOffset, const size_t initLength) :
    cstr(initStr + initOffset),
    length(initLength)
{
    //
}

Substring::Substring(const char *const initStr) :
    cstr(initStr),
    length(Substring::strlen(initStr))
{
    //
}

Substring::Substring(const Substring &ref) :
    cstr(ref.cstr),
    length(ref.length)
{
    //
}

char Substring::operator[](const size_t index) const {
    if (index >= length) {
        return '\0';
    }
    return cstr[index];
}

size_t Substring::getLength() const {
    return length;
}

bool Substring::isEmpty() const {
    return length == 0;
}

void Substring::copyTo(char *dest) const {
    const char *src = cstr;
    for (size_t i = 0; i < length; i++) {
        (*dest) = (*src);
        dest++;
        src++;
    }
    (*dest) = '\0';
}

Substring Substring::substring(const size_t newOffset) const {
    if (newOffset >= length) {
        return Substring();
    }
    // assert(newOffset < length);
    return Substring(cstr, newOffset, length - newOffset);
}

Substring Substring::substring(const size_t newOffset, const size_t newLength) const {
    if (newOffset >= length) {
        return Substring();
    }
    // assert(newOffset < length);
    const size_t max_new_length = length - newOffset;
    return Substring(
        cstr,
        newOffset,
        (newLength > max_new_length) ? max_new_length : newLength);
}

Substring Substring::removeHeadSpaces() const {
    size_t startingIndex = 0;
    const char *c_ptr = cstr;
    while ((startingIndex < length) && ((*c_ptr) == ' ')) {
        startingIndex++;
        c_ptr++;
    }
    return substring(startingIndex);
}

Substring Substring::removeTailSpaces() const {
    size_t newLength = length;
    const char *c_ptr = cstr + length - 1;
    while ((newLength > 0) && ((*c_ptr) == ' ')) {
        newLength--;
        c_ptr--;
    }
    return substring(0, newLength);
}

Substring Substring::trim() const {
    // could be further optimized
    // but I am too lazy right now
    return removeHeadSpaces().removeTailSpaces();
}

size_t Substring::indexOf(const char c) const {
    const char *c_ptr = cstr;
    for (size_t index = 0; index < length; index++) {
        if ((*c_ptr) == c) {
            return index;
        }
        c_ptr++;
    }
    // character not found
    return length;
}

size_t Substring::lastIndexOf(const char c) const {
    const char *c_ptr = cstr + length - 1;
    for (size_t len = length; len > 0; len--) {
        if ((*c_ptr) == c) {
            return len - 1;
        }
        c_ptr--;
    }
    // character not found
    return length;
}

size_t Substring::count(const char c) const {
    size_t counter = 0;
    const char *c_ptr = cstr;
    for (size_t i = 0; i < length; i++) {
        if ((*c_ptr) == c) {
            counter++;
        }
        c_ptr++;
    }
    return counter;
}

bool Substring::operator==(const char *str) const {
    const char *lhs = cstr;
    for (size_t i = 0; i < length; i++) {
        if ((*lhs) != (*str)) {
            return false;
        }
        lhs++;
        str++;
    }
    return (*str) == '\0';
}

bool Substring::operator==(const Substring &str) const {
    if (length != str.length) {
        return false;
    }
    if (cstr == str.cstr) {
        return true;
    }
    const char *lhs = cstr;
    const char *rhs = str.cstr;
    for (size_t i = 0; i < length; i++) {
        if ((*lhs) != (*rhs)) {
            return false;
        }
        lhs++;
        rhs++;
    }
    return true;
}

void Substring::split(const char divider, Substring *substrings) const {
    Substring s = (*this);
    do {
        const size_t index = s.indexOf(divider);
        (*substrings) = s.substring(0, index);
        substrings++;
        s = s.substring(index + 1);
    } while (s.getLength() > 0);
}

Substring &Substring::operator=(const char *const str) {
    cstr = str;
    length = Substring::strlen(str);
    return (*this);
}

Substring &Substring::operator=(const Substring &ref) {
    cstr = ref.cstr;
    length = ref.length;
    return (*this);
}

int Substring::compare(const Substring lhs, const Substring rhs) {
    size_t index = 0;
    while (true) {
        const signed char lc = (signed char)lhs[index];
        const signed char rc = (signed char)rhs[index];
        const signed char delta = lc - rc;
        if (delta != 0) {
            return delta;
        } else if (lc == '\0') { // lc == rc == '\0', thus lhs == rhs
            return 0;
        }
        index++;
    }
}

bool ino_interpreter::structs::util::operator<(const Substring lhs, const Substring rhs) {
    return Substring::compare(lhs, rhs) < 0;
}

bool ino_interpreter::structs::util::operator<=(const Substring lhs, const Substring rhs) {
    return Substring::compare(lhs, rhs) <= 0;
}

bool ino_interpreter::structs::util::operator>(const Substring lhs, const Substring rhs) {
    return Substring::compare(lhs, rhs) > 0;
}

bool ino_interpreter::structs::util::operator>=(const Substring lhs, const Substring rhs) {
    return Substring::compare(lhs, rhs) >= 0;
}
