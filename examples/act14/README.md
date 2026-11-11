<!--no-pdf-->
# Activity 14 Example

A child thread posts a named semaphore. Its parent waits before continuing. Every run prints the same three lines in the same order.

The `check` target runs the program and compares its complete output with `expected/run.txt`, so a change to any single printed line fails the check.

Run commands in this directory. On macOS, use the Ubuntu virtual machine from Bootcamp 1, Part 4. On Windows, use WSL2 Ubuntu. On Linux, use a terminal. You need a C compiler and `make`.

Build with `make`. Compare output with `make check`. Remove generated files with `make clean`.
