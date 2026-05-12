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
