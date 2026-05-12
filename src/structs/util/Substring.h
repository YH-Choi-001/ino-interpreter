/**
 * @file Substring.h Declaration of substring class.
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

#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <stddef.h>

namespace ino_interpreter {
    namespace structs {
        namespace util {

/**
 * The underlying (assumed immutable) C-string is reused
 * to avoid using heap exhaustively
 * like common string classes do.
 * 
 * @brief A substring of a C-string.
 */
class Substring {
    private:
        /**
         * @brief The (first byte of) underlying C-string.
         */
        const char *cstr;

        /**
         * @brief The length of this string.
         * Note that `cstr + length` != '\0' if the original C-string tail is chopped.
         */
        size_t length;

        /**
         * @brief Get the length of a C-string.
         * @param str The C-string to be processed.
         * @return The length of the C-string.
         */
        static size_t strlen(const char *str);

        /**
         * @brief Create a substring with all values initialized.
         * @param initStr The underlying C-string.
         * @param initOffset The offset of the substring.
         * @param initLength The length of the substring.
         */
        Substring(const char *const initStr, const size_t initOffset, const size_t initLength);

    public:
        /**
         * @brief Create an empty string.
         */
        Substring();

        /**
         * @brief Create a string from a C-string.
         * @param initStr The C-string to create from.
         */
        Substring(const char *const initStr);

        /**
         * @brief Create a copy of another string.
         * @param ref The string to be copied from.
         */
        Substring(const Substring &ref);

        /**
         * @brief Get one character from this string.
         * @param index The index of the character requested.
         * @return The character requested, or `'\0'` if (`index` >= `getLength()`).
         */
        char operator[](const size_t index) const;

        /**
         * @brief Get the length of this string.
         * @return The length of this string.
         */
        size_t getLength() const;

        /**
         * @brief Check whether this string is empty.
         * @return True if this string is empty, false otherwise.
         */
        bool isEmpty() const;

        /**
         * @brief Copy this string to a char array buffer.
         * @param dest The location of the char array buffer.
         * @note `dest` should have a minimal size of (getLength() + 1).
         */
        void copyTo(char *dest) const;

        /**
         * @brief Create a substring from a specific offset.
         * @param offset The index where the created substring begins (inclusive).
         * @return A substring that starts from `offset`, all the way to the end of the string.
         */
        Substring substring(const size_t offset) const;

        /**
         * @brief Create a substring from a specific offset with a specific length.
         * @param offset The index where the created substring begins (inclusive).
         * @param length The length of the created substring.
         * @return A substring that starts from `offset` with a length of `length`.
         */
        Substring substring(const size_t offset, const size_t length) const;

        /**
         * @brief Create a substring without spaces at the head.
         * @return A substring without spaces at the head.
         */
        Substring removeHeadSpaces() const;

        /**
         * @brief Create a substring without spaces at the tail.
         * @return A substring without spaces at the tail.
         */
        Substring removeTailSpaces() const;

        /**
         * @brief Create a substring without spaces on both ends.
         * @return a substring without spaces on both ends.
         */
        Substring trim() const;

        /**
         * @brief Get the index of first occurence of a character.
         * @param c The character to be checked.
         * @return The index of first occurence of the character `c`, or length if it doesn't exist.
         */
        size_t indexOf(const char c) const;

        /**
         * @brief Get the index of last occurence of a character.
         * @param c The character to be checked.
         * @return The index of last occurence of the character `c` or length if it doesn't exist.
         */
        size_t lastIndexOf(const char c) const;

        /**
         * @brief Count the occurence of a character.
         * @param c The character to be counted.
         * @return The occurence of the character `c`.
         */
        size_t count(const char c) const;

        /**
         * @brief Compare this string with another C-string.
         * @param str The other C-string to be compared.
         * @return `true` if both strings have the same content, `false` otherwise.
         */
        bool operator==(const char *str) const;

        /**
         * @brief Compare this string with another string.
         * @param str The other string to be compared.
         * @return `true` if both strings have the same content, `false` otherwise.
         */
        bool operator==(const Substring &str) const;

        /**
         * @brief Split this string into several substrings.
         * @param divider The character to divide this string.
         * @param substrings The buffer to hold the result substrings. Minimal size of `count(divider)` + 1.
         */
        void split(const char divider, Substring *substrings) const;

        /**
         * @brief Point to another C-string.
         * @param str The other C-string being pointed.
         * @return `*this`.
         */
        Substring &operator=(const char *const str);

        /**
         * @brief Point to another substring.
         * @param ref The other substring being pointed.
         * @return `*this`.
         */
        Substring &operator=(const Substring &ref);

        /**
         * @brief Compare 2 strings lexicographically.
         * @param lhs The left string.
         * @param rhs The right string.
         * @return 0 if `lhs` equals `rhs`, negative diff if `lhs` < `rhs`, positive diff if `lhs` > `rhs`.
         * @see strcmp
         */
        static int compare(const Substring lhs, const Substring rhs);
};

/**
 * @brief Compare 2 strings lexicographically.
 * @param lhs The left string.
 * @param rhs The right string.
 * @return `true` if `lhs` < `rhs`, `false` if `lhs` >= `rhs`.
 */
bool operator<(const Substring lhs, const Substring rhs);

/**
 * @brief Compare 2 strings lexicographically.
 * @param lhs The left string.
 * @param rhs The right string.
 * @return `true` if `lhs` <= `rhs`, `false` if `lhs` > `rhs`.
 */
bool operator<=(const Substring lhs, const Substring rhs);

/**
 * @brief Compare 2 strings lexicographically.
 * @param lhs The left string.
 * @param rhs The right string.
 * @return `true` if `lhs` > `rhs`, `false` if `lhs` <= `rhs`.
 */
bool operator>(const Substring lhs, const Substring rhs);

/**
 * @brief Compare 2 strings lexicographically.
 * @param lhs The left string.
 * @param rhs The right string.
 * @return `true` if `lhs` >= `rhs`, `false` if `lhs` < `rhs`.
 */
bool operator>=(const Substring lhs, const Substring rhs);

        }
    }
}

#endif // #ifndef SUBSTRING_H