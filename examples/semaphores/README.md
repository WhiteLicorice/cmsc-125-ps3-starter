<!--no-pdf-->
# Semaphores Example

A child thread posts a named semaphore. Its parent waits before continuing. Every run prints the same three lines in the same order.

The `check` target runs the program and compares its complete output with `expected/run.txt`, so a change to any single printed line fails the check.

Run commands in this directory. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
