/**
 * @file FunctionImplementation.h Declaration of function implementation class.
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

#ifndef INO_INTERPRETER_FUNCTION_IMPLEMENTATION_H
#define INO_INTERPRETER_FUNCTION_IMPLEMENTATION_H

#include "util/Substring.h"
#include "Argument.h"
#include "FunctionCall.h"

namespace ino_interpreter {
    namespace structs {
/**
 * @brief A function implementation.
 */
class FunctionImplementation {
    public:
        /**
         * @brief The return type.
         */
        typedef float return_t;

    private:
        /**
         * @brief The function implementation.
         */
        void *const func;

        /**
         * @brief The number of arguments in the function.
         */
        const size_t argCount;

        /**
         * @brief The return value when the implementation is not found.
         */
        static const return_t IMPLEMENTATION_NOT_FOUND;

        /**
         * @brief The return value when argument count of caller doesn't match.
         */
        static const return_t ARGCOUNT_MISMATCH;

        /**
         * @brief The return value when argument count is not supported.
         */
        static const return_t ARGCOUNT_UNSUPPORTED;

    protected:
        /**
         * @brief Create a function implementation.
         * @param argCount The number of arguments in the function.
         */
        FunctionImplementation(const size_t argCount);

    public:
        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)());

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(Argument));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(Argument, Argument));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(Argument, Argument, Argument));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(Argument, Argument, Argument, Argument));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(
            Argument,
            Argument,
            Argument,
            Argument,
            Argument
        ));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument
        ));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument
        ));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument
        ));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument
        ));

        /**
         * @brief Create a function implementation.
         * @param func The implementation of the function.
         */
        FunctionImplementation(return_t (*func)(
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument,
            Argument
        ));

        /**
         * @brief Copy a function declaration.
         * @param ref The function declaration being copied from.
         */
        FunctionImplementation(const FunctionImplementation &ref);

        /**
         * @brief Get the number of arguments in this function.
         * @return The number of arguements in this function.
         */
        size_t getArgCount() const;

        /**
         * @brief Execute the implementation of this function.
         * @param call The function call made to execute this function.
         * @return The data returned after executing this call.
         */
        virtual return_t execute(const FunctionCall &call) const;

        /**
         * @brief Check if this implementation has the same behaviour as the other implementation.
         * @param impl The other implementation being compared.
         * @return `true` if both implementations have the same behaviour, `false` otherwise.
         */
        bool operator==(const FunctionImplementation &impl) const;
};
    }
}

#endif // #ifndef INO_INTERPRETER_FUNCTION_IMPLEMENTATION_H
