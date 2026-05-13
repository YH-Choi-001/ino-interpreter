/**
 * @file FunctionRegistry.h Declaration of function registry class.
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

#ifndef INO_INTERPRETER_FUNCTION_REGISTRY_H
#define INO_INTERPRETER_FUNCTION_REGISTRY_H

#include "util/Substring.h"
#include "FunctionDeclaration.h"
#include "FunctionImplementation.h"

#include "cpp_data_structures_and_algorithms/src/structures/maps/SortedArrayMap.h"

namespace ino_interpreter {
    namespace structs {
/**
 * @brief A function registry.
 */
class FunctionRegistry {
    private:
        /**
         * @brief The Map data type from function declaration to implementation.
         */
        typedef yh::structures::maps::SortedArrayMap<FunctionDeclaration, FunctionImplementation> FunctionMap;

        /**
         * @brief The map data type from identifier substring to function registry.
         */
        typedef yh::structures::maps::SortedArrayMap<util::Substring, FunctionRegistry> SubRegistryMap;

        /**
         * @brief Functions under this registry.
         */
        FunctionMap functions;

        /**
         * @brief Sub-registries under this registry.
         */
        SubRegistryMap subRegistries;

    public:
        /**
         * @brief Create an empty function registry.
         */
        FunctionRegistry();

        /**
         * A deep copy is made.
         * @brief Copy a function registry.
         * @param ref The function registy being copied from.
         */
        FunctionRegistry(const FunctionRegistry &ref);

        /**
         * @brief Destroy this function registry.
         */
        ~FunctionRegistry();

        /**
         * @brief Insert a function declaration and implementation to this registry.
         * @param declaration The declaration of the function inserted.
         * @param implementation The implementation of the function inserted.
         */
        void insertFunction(
            FunctionDeclaration declaration,
            FunctionImplementation implementation
        );

        /**
         * @brief Insert a function implementation to this registry.
         * @param identifier The identifier of the function inserted.
         * @param implementation The implementation of the function inserted.
         */
        void insertFunction(
            util::Substring identifier,
            FunctionImplementation implementation
        );

        /**
         * @brief Get a function implementation in this registry by its declaration.
         * @param declaration The declaration of the function retrieved.
         * @return The corresponding function implementation, or nullptr if it does not exist.
         */
        FunctionImplementation *getFunction(FunctionDeclaration declaration);

        /**
         * @brief Remove a function from this registry.
         * @param declaration The declaration of the function removed.
         */
        void removeFunction(FunctionDeclaration declaration);

        /**
         * @brief Get the number of functions in this registry.
         * @return The number of functions in this registry.
         */
        size_t getFunctionCount();

        /**
         * A deep copy of the sub-registry will be made and inserted.
         * Modifying the original sub-registry will not affect the sub-registry under this registry.
         * @brief Insert a sub-registry under this registry.
         * @param identifier The identifier of the sub-registry inserted.
         * @param subRegistry The sub-registry to be inserted.
         */
        void insertSubRegistry(util::Substring identifier, FunctionRegistry &subRegistry);

        /**
         * @brief Get a sub-registry under this registry by its identifier.
         * @param identifier The identifier of the sub-registry retrieved.
         * @return The corresponding sub-registry, or nullptr if it does not exist.
         */
        FunctionRegistry *getSubRegistry(util::Substring identifier);

        /**
         * @brief Remove a sub-registry from this registry.
         * @param identifier The identifier of the sub-registry removed.
         */
        void removeSubRegistry(util::Substring identifier);

        /**
         * @brief Get the number of sub-registries under this registry.
         * @return The number of sub-registries under this registry.
         */
        size_t getSubRegistryCount();

        /**
         * @brief Resolve a function call.
         * @param call The function call to be resolved.
         * @param delimiter The delimiter separating registry identifiers.
         * @return The corresponding implementation for the function, or nullptr if it does not exist.
         */
        FunctionImplementation *resolve(const FunctionDeclaration &call, const char delimiter = '.');
};
    }
}

#endif // #ifndef INO_INTERPRETER_FUNCTION_REGISTRY_H
