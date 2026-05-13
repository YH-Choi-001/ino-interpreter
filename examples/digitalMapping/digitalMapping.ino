/**
 * @file digitalMapping.ino A mapping for simple digital I/Os only.
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
 * 
 * The copyright of Arduino API belongs to Arduino and their respective copyright holders.
 * The copyright notice above only covers the contents of this file,
 * which might not be applicable to Arduino API.
 */

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
