#include <InoInterpreter.h>

using ino_interpreter::InoInterpreter;
using ino_interpreter::structs::FunctionDeclaration;
using ino_interpreter::structs::FunctionImplementation;
using ino_interpreter::structs::FunctionRegistry;
using ino_interpreter::structs::Argument;

InoInterpreter interpreter;

void attachMapping() {
    FunctionRegistry &rootRegistry = interpreter.getRootRegistry();
    rootRegistry.insertFunction(
        FunctionDeclaration("pinMode", 2),
        FunctionImplementation([](Argument pin, Argument mode) { pinMode((int)pin, (int)mode); return 1.0f; })
    );
    rootRegistry.insertFunction(
        FunctionDeclaration("digitalWrite", 2),
        FunctionImplementation([](Argument pin, Argument state) { digitalWrite((int)pin, (int)state); return 1.0f; })
    );
    rootRegistry.insertFunction(
        FunctionDeclaration("digitalRead", 1),
        FunctionImplementation([](Argument pin) -> float { return digitalRead((int)pin); })
    );
}

void printWelcomingMessage() {
    Serial.println("Welcome to Ino Interpreter.");
    Serial.println("This example is a simplistic example");
    Serial.println("to allow you to use digitalWrite and digitalRead functions.");
    Serial.println("Simply type pinMode(13, 1) and digitalWrite(13, 1)");
    Serial.println("to test it out.");
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
