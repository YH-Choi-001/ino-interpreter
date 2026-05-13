/**
 * Implementation of ino interpreter class.
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

#include "InoInterpreter.h"
#include "structs/util/Substring.h"

using ino_interpreter::InoInterpreter;
using ino_interpreter::structs::FunctionCall;
using ino_interpreter::structs::FunctionDeclaration;
using ino_interpreter::structs::FunctionImplementation;
using ino_interpreter::structs::FunctionRegistry;
using ino_interpreter::structs::util::Substring;

using yh::structures::maps::Map;
using yh::structures::maps::SortedArrayMap;


FunctionRegistry &InoInterpreter::getRootRegistry() {
    return rootRegistry;
}

String InoInterpreter::executeSingleCommand(const Substring &cmd) {
    const Substring trimmedCmd(cmd.trim());
    if (trimmedCmd.isEmpty()) {
        return String();
    }
    FunctionCall fcall(trimmedCmd);
    FunctionImplementation *const impl = rootRegistry.resolve(fcall);
    if (impl == nullptr) {
        return "failed to resolve function call";
    }
    return String(impl->execute(fcall));
}

String InoInterpreter::execute(const String &rawCmds) {
    const char cmdDivider = ';';

    const Substring rawCmdsSubstring(rawCmds.c_str());
    const size_t semicolonCount = rawCmdsSubstring.count(cmdDivider);
    Substring cmds[semicolonCount + 1];
    rawCmdsSubstring.split(cmdDivider, cmds);

    String aggregatedResult = executeSingleCommand(cmds[0]);
    for (size_t i = 1; i < semicolonCount + 1; i++) {
        aggregatedResult += "; " + executeSingleCommand(cmds[i]);
    }

    return aggregatedResult;
}
