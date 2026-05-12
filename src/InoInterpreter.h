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
