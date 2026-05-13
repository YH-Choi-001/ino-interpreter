/**
 * Implementation of function registry class.
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

#include "FunctionRegistry.h"

using ino_interpreter::structs::FunctionRegistry;
using ino_interpreter::structs::FunctionImplementation;

FunctionRegistry::FunctionRegistry() {
    //
}

FunctionRegistry::FunctionRegistry(const FunctionRegistry &ref) {
    for (FunctionMap::Iterator it = (FunctionMap &)(ref.functions); it.hasNext(); it.proceed()) {
        FunctionMap::Entry *const entry = it.get();
        if (entry == nullptr) {
            continue;
        }
        this->insertFunction(*(entry->key), *(entry->value));
    }
    for (SubRegistryMap::Iterator it = (SubRegistryMap &)(ref.subRegistries); it.hasNext(); it.proceed()) {
        SubRegistryMap::Entry *const entry = it.get();
        if (entry == nullptr) {
            continue;
        }
        this->insertSubRegistry(*(entry->key), *(entry->value));
    }
}

FunctionRegistry::~FunctionRegistry() {
    functions.removeIf([](FunctionMap::Entry entry) {
        delete entry.key;
        delete entry.value;
        return true;
    });
    subRegistries.removeIf([](SubRegistryMap::Entry entry) {
        delete entry.key;
        delete entry.value;
        return true;
    });
}

void FunctionRegistry::insertFunction(FunctionDeclaration declaration, FunctionImplementation implementation) {
    functions.put(new FunctionDeclaration(declaration), new FunctionImplementation(implementation));
}

void FunctionRegistry::insertFunction(util::Substring identifier, FunctionImplementation implementation) {
    insertFunction(FunctionDeclaration(identifier, implementation.getArgCount()), implementation);
}

FunctionImplementation *FunctionRegistry::getFunction(FunctionDeclaration declaration) {
    return functions.get(&declaration);
}

void FunctionRegistry::removeFunction(FunctionDeclaration declaration) {
    for (FunctionMap::Iterator it = functions; it.hasNext(); it.proceed()) {
        FunctionMap::Entry *const entry = it.get();
        if (entry == nullptr) {
            continue;
        }
        if (declaration == (*(entry->key))) {
            delete entry->key;
            delete entry->value;
            it.remove();
            break;
        }
    }
}

size_t FunctionRegistry::getFunctionCount() {
    return functions.size();
}

void FunctionRegistry::insertSubRegistry(util::Substring identifier, FunctionRegistry &subRegistry) {
    subRegistries.put(new util::Substring(identifier), new FunctionRegistry(subRegistry));
}

FunctionRegistry *FunctionRegistry::getSubRegistry(util::Substring identifier) {
    return subRegistries.get(&identifier);
}

void FunctionRegistry::removeSubRegistry(util::Substring identifier) {
    for (SubRegistryMap::Iterator it = subRegistries; it.hasNext(); it.proceed()) {
        SubRegistryMap::Entry *const entry = it.get();
        if (entry == nullptr) {
            continue;
        }
        if (identifier == (*(entry->key))) {
            delete entry->key;
            delete entry->value;
            it.remove();
            break;
        }
    }
}

size_t FunctionRegistry::getSubRegistryCount() {
    return subRegistries.size();
}

FunctionImplementation *FunctionRegistry::resolve(const FunctionDeclaration &call, const char delimiter) {
    const util::Substring identifier = call.getIdentifier();
    const size_t delimiterCount = identifier.count(delimiter);
    util::Substring subIds [delimiterCount + 1];
    identifier.split(delimiter, subIds);

    FunctionRegistry *currentRegistry = this;
    for (size_t i = 0; i < delimiterCount; i++) {
        currentRegistry = currentRegistry->subRegistries.get(&(subIds[i]));
        if (currentRegistry == nullptr) {
            return nullptr;
        }
    }

    FunctionDeclaration leafCall(subIds[delimiterCount], call.getArgCount());
    return currentRegistry->functions.get(&leafCall);
}
