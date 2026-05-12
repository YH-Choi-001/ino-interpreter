#ifndef INO_INTERPRETER_ARGUMENT_H
#define INO_INTERPRETER_ARGUMENT_H

#include "util/Substring.h"

namespace ino_interpreter {
    namespace structs {
/**
 * @brief The argument of a function call.
 */
class Argument {
    private:
        /**
         * @brief The string representation of this argument.
         */
        const util::Substring stringRep;

        /**
         * @brief The numeric value parsed from this argument.
         */
        float value;

        // static size_t findIndexOfNonFloat(util::Substring str);

        /**
         * @brief Convert the string representation to a numeric value.
         */
        void setValue(util::Substring str);

        /**
         * @brief Illegal default constructor.
         */
        Argument();

    public:
        /**
         * @brief Create an argument from a substring.
         * @param str The string representation of this argument.
         */
        Argument(util::Substring str);

        /**
         * @brief Copy an argument.
         * @param ref The argument being copied.
         */
        Argument(const Argument &ref);

        /**
         * @brief Get the numeric value of this argument.
         * @return The numeric value of this argument.
         */
        operator float() const;

        /**
         * @brief Get the string representation of this argument.
         * @return The string representation of this argument.
         */
        operator util::Substring() const;
};
    }
}

#endif // #ifndef INO_INTERPRETER_ARGUMENT_H