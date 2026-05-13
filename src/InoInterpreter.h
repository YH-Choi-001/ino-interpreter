/**
 * @file InoInterpreter.h Declaration of ino-interpreter class.
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

#ifndef INO_INTERPRETER_INOINTERPRETER_H
#define INO_INTERPRETER_INOINTERPRETER_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdint>
#endif

#include "structs/FunctionCall.h"
#include "structs/FunctionDeclaration.h"
#include "structs/FunctionImplementation.h"
#include "structs/FunctionRegistry.h"
#include "structs/util/Substring.h"

namespace ino_interpreter {
    class InoInterpreter {
        private:
            structs::FunctionRegistry rootRegistry;
            String executeSingleCommand(const structs::util::Substring &cmd);
        public:
            structs::FunctionRegistry &getRootRegistry();
            String execute(const String &cmds);
    };

}

#endif // #ifndef INO_INTERPRETER_INOINTERPRETER_H
