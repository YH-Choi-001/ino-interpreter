/**
 * @file FunctionCall.h Declaration of function call class.
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

#ifndef INO_INTERPRETER_FUNCTION_CALL_H
#define INO_INTERPRETER_FUNCTION_CALL_H

#include "FunctionDeclaration.h"
#include "Argument.h"
#include "util/Substring.h"

namespace ino_interpreter {
    namespace structs {
/**
 * @brief A function call.
 */
class FunctionCall : public FunctionDeclaration {
    private:
        /**
         * @brief The array of arguments in this function call.
         */
        const Argument **args;

        /**
         * @brief Factory configurations.
         */
        struct factory_t {
            util::Substring identifier;
            size_t argCount;
            const Argument **args;
        };

        /**
         * @brief Create factory configurations from string representations.
         * @param stringRep The string representation of the fuction call.
         * @return The factory configurations.
         */
        static factory_t factory(util::Substring stringRep);

        /**
         * @brief Illegal default constructor.
         */
        FunctionCall();

        /**
         * @brief Illegal copy constructor.
         */
        FunctionCall(const FunctionCall &ref);

        /**
         * @brief Create a function call from a factory configuration.
         */
        FunctionCall(factory_t f);

    public:
        /**
         * @brief Create a fuction call from a string.
         * @param stringRep The string representation of this function call.
         */
        FunctionCall(util::Substring stringRep);

        /**
         * @brief Destroy this function call.
         */
        ~FunctionCall();

        /**
         * @brief Get an argument in this function call.
         * @param index The index of the argument in this function call [0, getArgCount()).
         * @return The `index`th argument in this function call, or nullptr if index is invalid.
         */
        const Argument *getArg(const size_t index) const;
};
    }
}

#endif // #ifndef INO_INTERPRETER_FUNCTION_CALL_H
