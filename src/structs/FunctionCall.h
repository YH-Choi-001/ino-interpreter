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
