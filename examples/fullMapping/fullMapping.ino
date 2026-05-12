#include <InoInterpreter.h>

using ino_interpreter::InoInterpreter;
using ino_interpreter::structs::FunctionDeclaration;
using ino_interpreter::structs::FunctionImplementation;
using ino_interpreter::structs::FunctionRegistry;
using ino_interpreter::structs::Argument;

InoInterpreter interpreter;

#define _INSERT_IMPL_0_PARAM(reg,id,prefix,suffix) { reg.insertFunction(#id, FunctionImplementation([]() -> float { prefix id() suffix })); }
#define _INSERT_IMPL_1_PARAM(reg,id,prefix,suffix) { reg.insertFunction(#id, FunctionImplementation([](Argument a) -> float { prefix id(a) suffix })); }
#define _INSERT_IMPL_2_PARAM(reg,id,prefix,suffix) { reg.insertFunction(#id, FunctionImplementation([](Argument a, Argument b) -> float { prefix id(a, b) suffix })); }
#define _INSERT_IMPL_3_PARAM(reg,id,prefix,suffix) { reg.insertFunction(#id, FunctionImplementation([](Argument a, Argument b, Argument c) -> float { prefix id(a, b, c) suffix })); }
#define _INSERT_IMPL_4_PARAM(reg,id,prefix,suffix) { reg.insertFunction(#id, FunctionImplementation([](Argument a, Argument b, Argument c, Argument d) -> float { prefix id(a, b, c, d) suffix })); }

#define SETTER_OK_VALUE (1.0f)
#define _RETURN_SETTER() { return SETTER_OK_VALUE; }

#define INSERT_SETTER(reg,id,argCount) { _INSERT_IMPL_##argCount##_PARAM(reg,id,,;_RETURN_SETTER();); }
#define INSERT_GETTER(reg,id,argCount) { _INSERT_IMPL_##argCount##_PARAM(reg,id,return ,;); }

void attachMapping() {
    FunctionRegistry &rootRegistry = interpreter.getRootRegistry();

    // digital I/O
    INSERT_SETTER(rootRegistry, pinMode, 2);
    INSERT_SETTER(rootRegistry, digitalWrite, 2);
    INSERT_GETTER(rootRegistry, digitalRead, 1);

    // analog I/O
    INSERT_GETTER(rootRegistry, analogRead, 1);
    INSERT_SETTER(rootRegistry, analogWrite, 2);

    // disabled due to asynchronous nature
    // // external interrupts
    // INSERT_SETTER(rootRegistry, attachInterrupt, 3);
    // INSERT_SETTER(rootRegistry, detachInterrupt, 1);
    // INSERT_GETTER(rootRegistry, digitalPinToInterrupt, 1);

    // advanced I/O
    INSERT_GETTER(rootRegistry, pulseIn, 2);
    INSERT_GETTER(rootRegistry, pulseIn, 3);
    INSERT_GETTER(rootRegistry, pulseInLong, 2);
    INSERT_GETTER(rootRegistry, pulseInLong, 3);
    INSERT_GETTER(rootRegistry, shiftIn, 3);
    INSERT_SETTER(rootRegistry, shiftOut, 4);
    INSERT_SETTER(rootRegistry, tone, 2);
    INSERT_SETTER(rootRegistry, tone, 3);
    INSERT_SETTER(rootRegistry, noTone, 1);

    // interrupts
    INSERT_SETTER(rootRegistry, interrupts, 0);
    INSERT_SETTER(rootRegistry, noInterrupts, 0);

    // time
    INSERT_SETTER(rootRegistry, delay, 1);
    INSERT_SETTER(rootRegistry, delayMicroseconds, 1);
    INSERT_GETTER(rootRegistry, micros, 0);
    INSERT_GETTER(rootRegistry, millis, 0);
}

void printWelcomingMessage() {
    Serial.println("Welcome to Ino Interpreter.");
    Serial.println();
}

void setup() {
    Serial.begin(9600);

    // attach mapping to the interpreter
    attachMapping();

    // wait for user to open serial monitor
    while (!Serial) {}

    printWelcomingMessage();
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        if (input.length() > 0) {
            const size_t removingIndex = input.length() - 1;
            if (input.charAt(removingIndex) == '\r') {
                // Remove carriage return if it exists.
                input = input.substring(0, removingIndex);
            }
        }
        Serial.print(">>> ");
        Serial.println(input);
        const String output = interpreter.execute(input);
        Serial.print("<<< ");
        Serial.println(output);
    }
}
