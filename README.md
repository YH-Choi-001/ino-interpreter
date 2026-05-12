# Ino Interpreter

A simplistic REPL interpreter for Arduino.

This interpreter is kept minimal to facilitate a live hardware interaction only.
A lot of features are missing, such as variables, nested function calls, branching.

## Usage

Compile and upload the [`fullMapping.ino`](examples/fullMapping/fullMapping.ino) sketch to an Arduino.

You can run a function like this:
```cpp
analogRead(2)
```

Multiple functions could be passed together, separated by semicolons, to be executed sequentially.

An example blink program could be like this:
```cpp
pinMode(13, 1); digitalWrite(13, 1); delay(1000); digitalWrite(13, 0); delay(1000);
```

To time a function, you could program it like this:
```cpp
micros(); pinMode(13, 0); micros()
```

To measure distance on an HC-SR04, you could do this:
```cpp
pinMode(2, 1); pinMode(3, 0); 
digitalWrite(2, 1); digitalWrite(2, 0); pulseIn(3, 1);
```
which would give you the period of pin 3 is HIGH.
