<!--no-pdf-->
# Condition Variables Example

A producer places one item in a one-slot buffer. A consumer waits on a condition variable until the buffer holds that item. The program prints one line. It's the same on every run.

## The Model

The consumer starts first and locks the mutex. The buffer is empty, so it waits on the condition variable, and that call releases the mutex. The producer then locks, stores 42, sets the full flag, signals, and unlocks. The consumer wakes, reacquires the mutex, and finds the full flag set. It copies 42 out and clears the flag. The `while` loop tests the predicate again after every wake. That second test stops a spurious wake from reading an empty buffer.

The check compares the program's complete output against the checked-in expected file.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
