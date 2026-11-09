/**
 * @file printers.h GoogleTest value printers for the interpreter's structs.
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
 */

#ifndef PRINTERS_H
#define PRINTERS_H

#include <cstddef>
#include <ostream>

#include "../src/structs/util/Substring.h"
#include "../src/structs/Argument.h"
#include "../src/structs/FunctionCall.h"
#include "../src/structs/FunctionImplementation.h"

// GoogleTest finds these through argument-dependent lookup,
// so they must live in the same namespaces as the types they print.

namespace ino_interpreter {
    namespace structs {
        namespace util {
            inline std::ostream &operator<<(std::ostream &os, const Substring &str) {
                const size_t len = str.getLength();
                for (size_t i = 0; i < len; i++) {
                    os << str[i];
                }
                return os;
            }
        }

        inline std::ostream &operator<<(std::ostream &os, const Argument &arg) {
            return os << (util::Substring)arg;
        }

        inline std::ostream &operator<<(std::ostream &os, const FunctionCall &fc) {
            os << (util::Substring)fc.getIdentifier() << "(";
            for (size_t i = 0; i < fc.getArgCount(); i++) {
                const Argument *const arg = fc.getArg(i);
                if (i > 0) {
                    os << ", ";
                }
                if (arg == nullptr) {
                    os << "null";
                } else {
                    os << (*arg);
                }
            }
            return os << ")";
        }

        inline std::ostream &operator<<(std::ostream &os, const FunctionImplementation &fi) {
            return os << "fi of " << fi.getArgCount() << " arguments";
        }
    }
}

#endif // #ifndef PRINTERS_H
