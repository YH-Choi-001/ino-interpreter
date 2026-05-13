/**
 * @file FunctionDeclaration.h Declaration of function declaration class.
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

#ifndef INO_INTERPRETER_FUNCTION_DECLARATION_H
#define INO_INTERPRETER_FUNCTION_DECLARATION_H

#include "util/Substring.h"

namespace ino_interpreter {
    namespace structs {
/**
 * @brief A function declaration.
 */
class FunctionDeclaration {
    private:
        /**
         * @brief The identifier string of the function.
         */
        const util::Substring identifier;

        /**
         * @brief The number of arguments in the function.
         */
        const size_t argCount;

    public:
        /**
         * @brief Create a function declaration.
         * @param identifier The identifier stirng of the function.
         * @param argCount The number of arguments in the function.
         */
        FunctionDeclaration(const util::Substring identifier, const size_t argCount);

        /**
         * @brief Copy a function declaration.
         * @param ref The function declaration being copied from.
         */
        FunctionDeclaration(const FunctionDeclaration &ref);

        /**
         * @brief Get the identifier of this function call.
         * @return The identifier string of this function call.
         */
        util::Substring getIdentifier() const;

        /**
         * @brief Get the number of arguments in this function call.
         * @return The number of arguements in this function call.
         */
        size_t getArgCount() const;

        /**
         * @brief Compare whether 2 function declarations are equal.
         * @param rhs The other function declaration compared against.
         * @return `true` if both function declarations are equal, `false` otherwise.
         */
        bool operator==(const FunctionDeclaration &rhs) const;

        /**
         * First their identifiers are compared lexicographically.
         * If they share the same identifier (overloading),
         * their number of arguments will be compared.
         * @brief Compare 2 function declarations.
         * @param lhs The left function declaration.
         * @param rhs The right function declaration.
         * @return 0 if `lhs` equals `rhs`, negative diff if `lhs` < `rhs`, positive diff if `lhs` > `rhs`.
         * @see strcmp
         */
        static int compare(const FunctionDeclaration &lhs, const FunctionDeclaration &rhs);

        bool operator<(const FunctionDeclaration &rhs) const;

        bool operator<=(const FunctionDeclaration &rhs) const;

        bool operator>(const FunctionDeclaration &rhs) const;

        bool operator>=(const FunctionDeclaration &rhs) const;
};
    }
}

#endif // #ifndef INO_INTERPRETER_FUNCTION_DECLARATION_H