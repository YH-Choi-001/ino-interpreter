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