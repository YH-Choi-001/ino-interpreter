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
