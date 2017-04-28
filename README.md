# arduino-threads

A library to emulate threads on Arduino and other platforms without native threads, based on [Roman Black's work](http://www.romanblack.com/PICthread.htm).

You can see a basic example in `test.cpp`, or a more developed one in `motors.ino`.

## Gotchas

You can't use `THREAD_BREAK` inside `if`, `for`, `while`, and in general everything that uses braces.