# arduino-threads

A library to emulate threads on Arduino and other platforms without native threads.

You can see a working example in `test.cpp`.

## Gotchas

You can't use `THREAD_BREAK` inside `if`, `for`, `while`, and in general everything that uses braces.